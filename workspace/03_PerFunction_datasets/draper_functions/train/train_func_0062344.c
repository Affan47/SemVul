fd_get_pageinfo(int fd, struct file_pageinfo *pi)
{
    int PAGESIZE;
    void *file;
    struct byterange *br = NULL;
    struct stat st;
    unsigned char *page_vec = NULL;

    PAGESIZE = getpagesize();

    if(pi->fd != fd) {
        DEBUG("fd_get_pageinfo BUG, pi->fd != fd\n");
        return NULL;
    }
    pi->fd = fd;
    pi->unmapped = NULL;

    if(fstat(fd, &st) == -1 || !S_ISREG(st.st_mode))
        return NULL;
    pi->size = st.st_size;
    pi->nr_pages = (st.st_size + PAGESIZE - 1) / PAGESIZE;
    DEBUG("fd_get_pageinfo(fd=%d): st.st_size=%ld, nr_pages=%ld\n",
            fd, st.st_size, pi->nr_pages);


    if(pi->size == 0)
        return pi;


    file = mmap(NULL, st.st_size, PROT_NONE, MAP_SHARED, fd, 0);
    if(file == MAP_FAILED) {
        DEBUG("fd_get_pageinfo(fd=%d): mmap failed (don't worry), errno:%d, %s\n",
                fd, errno, strerror(errno));
        return pi;
    }

    page_vec = calloc(sizeof(*page_vec), pi->nr_pages);
    if(!page_vec) {
        DEBUG("calloc failed: size=%zd on fd=%d\n", pi->nr_pages, fd);
        goto cleanup;
    }

    if(mincore(file, pi->size, page_vec) == -1)
        goto cleanup;

    munmap(file, st.st_size);
    file = NULL;


    pi->nr_pages_cached = pi->nr_pages;
    size_t i, start = 0;
    for(i = 0; i < pi->nr_pages; i++) {
        if(!(page_vec[i] & 1))
            continue;
        if(start < i) {
            insert_into_br_list(pi, &br, start * PAGESIZE,
                (i - start) * PAGESIZE);
            pi->nr_pages_cached -= i - start;
        }
        start = i + 1;
    }

    if(start < pi->nr_pages) {
        insert_into_br_list(pi, &br, start * PAGESIZE,
                pi->size - start * PAGESIZE);
        pi->nr_pages_cached -= pi->nr_pages - start;
    }

    free(page_vec);

    return pi;

cleanup:
    if(file)
        munmap(file, st.st_size);
    free(page_vec);
    return NULL;
}
