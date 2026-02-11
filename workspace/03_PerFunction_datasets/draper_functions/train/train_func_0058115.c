replace_deferred_assignment(ast_sent* s, gm_symtab_entry *target_old, gm_symtab_entry* target_new) {
    gm_replace_da_t T;
    T.replace_da(target_old, target_new, s);
}
