qtreetbl_find_max(qtreetbl_t *tbl, size_t *namesize) {
    qtreetbl_lock(tbl);
    qtreetbl_obj_t *obj = find_max(tbl->root);
    if (obj == NULL) {
        errno = ENOENT;
        qtreetbl_unlock(tbl);
        return NULL;
    }

    if (namesize != NULL) {
        *namesize = obj->namesize;
    }
    void *name = qmemdup(obj->name, obj->namesize);
    qtreetbl_unlock(tbl);
    return name;
}
