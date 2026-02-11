construct_gain_memory_access_region(real ***funcgain, real ***subgain,
				    IntSet funcset, IntSet subrset)
{
    Module_table *m;
    real **funcret, **subret;
    int funcmax = get_max_module_entry(MODULE_FUNC);
    int subrmax = get_max_module_entry(MODULE_SUB);
    int marmax;

    funcret = calloc(funcmax + 1, sizeof(real *));
    subret = calloc(subrmax + 1, sizeof(real *));
    if (funcret == NULL || subret == NULL) {
        fatal("No Room\n");
    }
    for (m = module_head; m != NULL; m = m->next) {
        marmax = get_max_memory_access_table_entry(m->memory_access_region_head);
        if (marmax != -1) {
            if (m->kind == MODULE_FUNC) {
                funcret[m->entry] = calloc(marmax + 1, sizeof(real));
                if (funcret[m->entry] == NULL) {
                    fatal("No Room\n");
                }
            } else if (m->kind != MODULE_BLOCKDATA) {
                subret[m->entry] = calloc(marmax + 1, sizeof(real));
                if (subret[m->entry] == NULL) {
                    fatal("No Room\n");
                }
            }
        }
    }
    *funcgain = funcret;
    *subgain = subret;
}
