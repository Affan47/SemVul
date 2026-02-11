add_syminfo_struct(gm_symtab_entry * sym, bool is_scalar, int scope) {
    ast_extra_info* info = sym->find_info(GPS_TAG_BB_USAGE);
    gps_syminfo* syminfo;
    if (info == NULL) {
        syminfo = new gps_syminfo(is_scalar);
        sym->add_info(GPS_TAG_BB_USAGE, syminfo);
    } else {
        syminfo = (gps_syminfo*) info;
    }

    syminfo->set_scope(scope);
}
