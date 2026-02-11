replace_arg_var_semnode(Block *block)
{
    SemTree **arg_var_tbl;
    int vmax = get_max_var_entry(block->module->var_head);
    int i;

    if (block->inner == NULL) {
        return;
    }

    arg_var_tbl = calloc(sizeof(SemTree*), vmax + 1);
    if (arg_var_tbl == NULL) {
        fatal("No room.\n");
    }

    make_arg_var_tbl(block, arg_var_tbl);

    replace_arg_var_array_du_semnode(block->array_info->MayUse,
                                     arg_var_tbl,
                                     vmax);
    replace_arg_var_array_du_semnode(block->array_info->MayMod,
                                     arg_var_tbl,
                                     vmax);
    replace_arg_var_array_du_semnode(block->array_info->ExposedUse,
                                     arg_var_tbl,
                                     vmax);
    replace_arg_var_array_du_semnode(block->array_info->Kill,
                                     arg_var_tbl,
                                     vmax);

    for (i = 0; i < vmax + 1; i++) {
        if (arg_var_tbl[i] != NULL) {
            semtree_destruct(arg_var_tbl[i]);
        }
    }
    free(arg_var_tbl);
}
