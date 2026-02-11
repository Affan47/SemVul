do_generate_scalar_broadcast_send(gm_gps_basic_block* b) {

    std::map<gm_symtab_entry*, gps_syminfo*>& syms = b->get_symbols();
    std::map<gm_symtab_entry*, gps_syminfo*>::iterator I;
    for (I = syms.begin(); I != syms.end(); I++) {
        gps_syminfo* local_info = I->second;
        gps_syminfo* global_info = (gps_syminfo*) I->first->find_info(GPS_TAG_BB_USAGE);
        if (!global_info->is_scalar()) continue;
        if (local_info->is_used_as_reduce()) {
            int reduce_type = local_info->get_reduce_type();


            get_lib()->generate_broadcast_reduce_initialize_master(I->first->getId(), Body, reduce_type,
                    get_reduce_base_value(reduce_type, I->first->getType()->getTypeSummary()));

            continue;
        }
        if (!global_info->is_used_in_master() && !global_info->is_argument()) continue;
        if (local_info->is_used_as_rhs() && !global_info->is_argument()) {

            get_lib()->generate_broadcast_send_master(I->first->getId(), Body);
        }
    }
}
