fs_ptree_close(fs_ptree *pt)
{
    if (!pt) {
        fs_error(LOG_ERR, "tried to close NULL ptree");

        return 1;
    }
    if (!pt->filename) {
        fs_error(LOG_ERR, "tried to close already closed ptree");

        return 1;
    }
    if (munmap(pt->ptr, pt->file_length) == -1) {
        fs_error(LOG_CRIT, "failed to unmap '%s'", pt->filename);
    }
    flock(pt->fd, LOCK_UN);
    close(pt->fd);
    pt->fd = -1;
    g_free(pt->filename);
    pt->filename = NULL;
    free(pt);

    return 0;
}
