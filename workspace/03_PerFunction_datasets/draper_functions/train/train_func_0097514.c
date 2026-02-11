bind_tgtdefn(const tgtdefn_t *tgt)

{   bound_tgtdefn_t *bound;
    keymanager_t *km;
    FILE *fp_key=NULL;

    if (tgt == NULL) return NULL;

    build_keymgrs();
    bound = alloc_boundtgt(tgt);
    if (tgt->key.filename != NULL) {
        fp_key = fopen(tgt->key.filename, "rb");
    }

    km = keymgrs;
    while (km != NULL) {
        if (fp_key != NULL) (void)fseek(fp_key, 0L, SEEK_SET);
        if (km->bind(bound, fp_key)) {
            bound->keymgr = init_keymanager(km);
            break;
        }
        km = km->next;
    }

    if (bound->keymgr == NULL) {
        free_boundtgt(bound);
        bound = NULL;
    }

    if (fp_key != NULL) fclose(fp_key);

    return bound;
}
