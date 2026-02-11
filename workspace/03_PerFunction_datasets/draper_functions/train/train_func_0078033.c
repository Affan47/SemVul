generate_idlist(ast_idlist* idl) {
    int z = idl->get_length();
    for (int i = 0; i < z; i++) {
        ast_id* id = idl->get_item(i);
        generate_lhs_id(id);
        if (i < z - 1) Body.push_spc(',');
    }
}
