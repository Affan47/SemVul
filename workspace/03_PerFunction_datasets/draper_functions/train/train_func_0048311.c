jk_map_get_id(jk_map_t *m, const char *name)
{
    int rc = -1;
    if (m && name) {
        unsigned int i;
        unsigned int key;
        COMPUTE_KEY_CHECKSUM(name, key)
        for (i = 0; i < m->size; i++) {
            if (m->keys[i] == key && strcmp(m->names[i], name) == 0) {
                rc = i;
                break;
            }
        }
    }

    return rc;
}
