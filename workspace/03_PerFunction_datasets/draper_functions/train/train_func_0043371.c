is_conflict(list_t& L, gm_symtab_entry* t, gm_symtab_entry* b, int r_type, bool &is_bound_error, bool &is_type_error) {
    list_t::iterator i;
    is_type_error = false;
    is_bound_error = false;
    for (i = L.begin(); i != L.end(); i++) {
        bound_info_t* db = *i;
        if (db->target == t) {
            if (db->bound != b) {
                is_bound_error = true;
                return true;
            } else if (db->reduce_type != r_type) {
                is_type_error = true;
                return true;
            }
        }
    }
    return false;
}
