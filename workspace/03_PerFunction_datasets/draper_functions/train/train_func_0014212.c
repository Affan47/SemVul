work_run_freemem(work_t* work, void* ptr) {
    if (!ptr) {
        return;
    }
    switch (work->mem_usage) {
        case mem_none:

            break;
        case mem_malloc:
            TRACE("work %d: Freeing memory with free()\n", work->id);
            free(ptr);
            break;
        case mem_mmap:
            TRACE("work %d: Freeing memory with munmap()\n", work->id);
            munmap(ptr, work->mem_size);
            break;
        default:
            ERROR("Unknown memory usage type: %d\n", work->mem_usage);
    }
}
