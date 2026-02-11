scalar_has_exposed_use_statement(int def_entry, Block *block, Block *loop)
{
    Statement     *use_stm;
    Def_use_table *use_var;

    if (block->pre_head == NULL) {
        return FALSE;
    }

    use_stm = block->pre_head->stm_head;
    while(use_stm != NULL) {
        use_var = use_stm->use_var_list;
        while(use_var != NULL) {
            Var_table *def_vpt;
            Var_table *use_vpt;

            if (use_var->entry == def_entry) {
                if (scalar_has_no_def_in_dom(def_entry, use_stm, block, loop)) {
                    return TRUE;
                }
            }
            def_vpt = search_var_table(loop->module->var_head, def_entry);
            use_vpt = search_var_table(loop->module->var_head, use_var->entry);
            if ((def_vpt->kind == MEM_LM) || (use_vpt->kind == MEM_LM)) {
                if (def_vpt->name == use_vpt->name) {
                    if (scalar_has_no_def_in_dom(use_var->entry,
                                                 use_stm, block, loop)) {
                        return TRUE;
                    }
                }
            }

            use_var = use_var->next;
        }

        use_stm = use_stm->next;
    }

    return FALSE;
}
