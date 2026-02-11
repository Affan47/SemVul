fs_list_sort_chunk(fs_list *l, off_t start, off_t length, int (*comp)(const void *, const void *))
{

    void *map = mmap(NULL, length * l->width, PROT_READ | PROT_WRITE,
                     MAP_FILE | MAP_SHARED, l->fd, start * l->width);
    if (map == (void *)-1) {
        fs_error(LOG_ERR, "failed to map '%s', %lld+%lld for sort: %s",
                 l->filename, (long long)start * l->width,
                 (long long)length * l->width, strerror(errno));

        return 1;
    }

    qsort(map, length, l->width, comp);

    munmap(map, length * l->width);

    return 0;
}
