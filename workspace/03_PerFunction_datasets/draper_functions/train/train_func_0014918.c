fs_rhash_write_header(fs_rhash *rh)
{
    struct rhash_header header;

    header.id = FS_RHASH_ID;
    header.size = rh->size;
    header.count = rh->count;
    header.search_dist = rh->search_dist;
    header.bucket_size = rh->bucket_size;
    header.revision = rh->revision;
    memset(&header.padding, 0, sizeof(header.padding));
    if (pwrite(rh->fd, &header, sizeof(header), 0) == -1) {
        fs_error(LOG_CRIT, "failed to write header on %s: %s",
                 rh->filename, strerror(errno));

        return 1;
    }

    return 0;
}
