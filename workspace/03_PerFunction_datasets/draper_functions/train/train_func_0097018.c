_load_segments(void)
{
    FILE *fp;
    char line[1024];
    struct map_segment_desc seg;

    memheap_context.n_segments = 0;

    fp = fopen("/proc/self/maps", "r");
    if (NULL == fp) {
        MEMHEAP_ERROR("Failed to open /proc/self/maps");
        return OSHMEM_ERROR;
    }

    while (NULL != fgets(line, sizeof(line), fp)) {
        memset(&seg, 0, sizeof(seg));
        sscanf(line,
               "%llx-%llx %s %llx %s %llx %s",
               (long long *) &seg.start,
               (long long *) &seg.end,
               seg.perms,
               (long long *) &seg.offset,
               seg.dev,
               (long long *) &seg.inode,
               seg.pathname);

        if (OSHMEM_ERROR == _check_address(&seg))
            continue;

        if (OSHMEM_ERROR == _check_pathname(&seg))
            continue;

        if (OSHMEM_ERROR == _check_perms(&seg))
            continue;

        MEMHEAP_VERBOSE(5, "add: %s", line);
        if (MCA_MEMHEAP_MAX_SEGMENTS <= memheap_context.n_segments) {
            MEMHEAP_ERROR("too many segments (max = %d): skip %s",
                          MCA_MEMHEAP_MAX_SEGMENTS, line);
            continue;
        }
        if (memheap_context.n_segments > 0
                && seg.start
                        == memheap_context.mem_segs[memheap_context.n_segments
                                - 1].end) {
            MEMHEAP_VERBOSE(5, "Coalescing segment");
            memheap_context.mem_segs[memheap_context.n_segments - 1].end =
                    seg.end;
        } else {
            memheap_context.mem_segs[memheap_context.n_segments].start =
                    seg.start;
            memheap_context.mem_segs[memheap_context.n_segments].end = seg.end;
            memheap_context.n_segments++;
        }
    }

    fclose(fp);
    return OSHMEM_SUCCESS;
}
