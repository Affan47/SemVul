qtreetbl_debug(qtreetbl_t *tbl, FILE *out) {
    if (out == NULL) {
        errno = EIO;
        return false;
    }

    qtreetbl_lock(tbl);

    qtreetbl_unlock(tbl);

    return true;
}
