puredb_read(PureDB * const db, const off_t offset, const size_t len)
{
    void *buf;

    if ((buf = malloc(len + (size_t) 1U)) == NULL) {
        return NULL;
    }
#ifdef USE_MAPPED_IO
    if (db->map != NULL) {
        memcpy(buf, db->map + offset, len);
    } else
#endif
    {
        if (lseek(db->fd, offset, SEEK_SET) == (off_t) -1 ||
            safe_read(db->fd, buf, len) != (ssize_t) len) {
            free(buf);
            return NULL;
        }
    }
    ((unsigned char *) buf)[len] = 0U;

    return buf;
}
