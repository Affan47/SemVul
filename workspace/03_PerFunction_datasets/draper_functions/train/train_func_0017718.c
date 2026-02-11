traverse_expr_for_readset_adding_builtin(ast_expr_builtin* builtin, gm_rwinfo_map& rset, temp_map_t& DrvMap) {

    std::list<ast_expr*>& args = builtin->get_args();
    std::list<ast_expr*>::iterator I;
    for (I = args.begin(); I != args.end(); I++) {
        ast_expr* a = *I;
        traverse_expr_for_readset_adding(a, rset, DrvMap);
    }


    if (!builtin->driver_is_field() && builtin->get_driver()!=NULL) {
        ast_id* id = builtin->get_driver();
        gm_rwinfo* new_entry = gm_rwinfo::new_scala_inst(id);
        gm_symtab_entry* sym = id->getSymInfo();
        gm_add_rwinfo_to_set(rset, sym, new_entry, false);
    }
}
