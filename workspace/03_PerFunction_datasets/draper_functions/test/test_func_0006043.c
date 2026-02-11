lm_var_info_new(Var_table *var, Block *scope_block)
{
    Lm_var_info *p;

    p = (Lm_var_info *)malloc(sizeof(Lm_var_info));
    if (p == NULL) {
        fprintf(stderr, "malloc failed\n");
        exit(-1);
    }

    p->var = var;
    p->entry = var->entry;
    p->type = var->type;
    p->lm_var_id = 0;
    p->scope_block = scope_block;

    return p;
}
