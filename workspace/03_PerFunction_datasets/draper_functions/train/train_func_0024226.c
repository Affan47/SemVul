jk_reset_pool(jk_pool_t *p)
{
    if (p->dyn_pos && p->dynamic) {
        size_t i;
        for (i = 0; i < p->dyn_pos; i++) {
            if (p->dynamic[i]) {
                free(p->dynamic[i]);
            }
        }
    }

    p->dyn_pos = 0;
    p->pos = 0;
}
