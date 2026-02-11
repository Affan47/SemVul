map_bc(fs_tbchain *bc, long length, long size)
{
    if (!bc) {
        fs_error(LOG_ERR, "tried to map NULL chain");

        return 1;
    }

    bc->len = (size + 1) * sizeof(fs_tblock) + sizeof(struct fs_tbc_header);
    if (lseek(bc->fd, bc->len, SEEK_SET) == -1) {
        fs_error(LOG_CRIT, "failed to seek in chain file %s: %s", bc->filename, strerror(errno));
    }
    if (bc->flags & (O_RDWR | O_WRONLY) && write(bc->fd, "", 1) == -1) {
        fs_error(LOG_CRIT, "failed to init chain file %s (fd %d): %s", bc->filename, bc->fd, strerror(errno));
    }
    int mflags = PROT_READ;
    if (bc->flags & (O_RDWR | O_WRONLY)) mflags |= PROT_WRITE;
    bc->ptr = mmap(NULL, bc->len, mflags, MAP_FILE | MAP_SHARED, bc->fd, 0);
    if (bc->ptr == (void *)-1 || bc->ptr == NULL) {
        fs_error(LOG_CRIT, "failed to mmap: %s", strerror(errno));

        return 1;
    }
    bc->header = (struct fs_tbc_header *)(bc->ptr);
    if (mflags & PROT_WRITE) {
        bc->header->id = TBCHAIN_ID;
        bc->header->size = size;
        bc->header->length = length;
    }
    bc->data = (fs_tblock *)(((char *)bc->ptr) + sizeof(struct fs_tbc_header));

    return 0;
}
