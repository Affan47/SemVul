add_all_defs_into_context(reaching_context_t& C, gm_defined_symbol_map& DI, ast_node *n)
{

    if (DI.find(n) != DI.end()) {
        std::vector<gm_symbol_def_t> &V = DI[n];
        std::vector<gm_symbol_def_t>::iterator v;

        for (v=V.begin(); v!=V.end(); v++)
        {
            gm_symbol_def_t def = *v;
            gm_symtab_entry* sym = def.first;
            ast_node* def_node = def.second;
            add_def(C, sym, def_node);
        }
    }
}
