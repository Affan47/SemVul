gps_bb_traverse_ast(gm_gps_basic_block* entry, gps_apply_bb_ast* apply, bool is_post, bool is_pre) {
    apply->set_is_post(is_post);
    apply->set_is_pre(is_pre);


    gps_bb_apply_only_once(entry, apply);

}
