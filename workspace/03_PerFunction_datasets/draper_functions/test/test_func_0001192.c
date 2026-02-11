is_symbol_defined_in_bb(gm_gps_basic_block* b, gm_symtab_entry *e) {
    std::map<gm_symtab_entry*, gps_syminfo*>& SYMS = b->get_symbols();
    if (SYMS.find(e) == SYMS.end())
        return false;
    else
        return true;
}
