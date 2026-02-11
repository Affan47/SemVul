merge_for_sentblock(ast_sentblock* s, gm_rwinfo_map& target, gm_rwinfo_map& old, bool is_reduce) {
    bool is_okay = true;
    gm_rwinfo_map::iterator i;
    for (i = old.begin(); i != old.end(); i++) {
        gm_symtab_entry* e = i->first;
        bool is_current_level;

        if (e->getType()->is_property()) {
            is_current_level = s->get_symtab_field()->is_entry_in_the_tab(e);
        } else {
            is_current_level = s->get_symtab_var()->is_entry_in_the_tab(e);
        }

        if (is_current_level) {

            continue;
        }


        gm_rwinfo_list* l = i->second;
        gm_rwinfo_list::iterator ii;
        for (ii = l->begin(); ii != l->end(); ii++) {
            gm_rwinfo* copy = (*ii)->copy();
            bool b = gm_add_rwinfo_to_set(target, e, copy, is_reduce);
            is_okay = is_okay && b;
        }
    }
    return is_okay;
}
