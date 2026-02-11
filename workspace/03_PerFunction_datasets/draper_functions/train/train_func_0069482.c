do_generate_vertex_states() {
    char temp[1024];
    Body.pushln("@Override");
    Body.pushln("public void compute(Iterable<MessageData> _msgs) {");
    get_lib()->generate_receive_state_vertex("_state_vertex", Body);

    Body.pushln("switch(_state_vertex) { ");
    gm_gps_beinfo * info = (gm_gps_beinfo *) FE.get_current_backend_info();
    std::list<gm_gps_basic_block*>& bb_blocks = info->get_basic_blocks();
    std::list<gm_gps_basic_block*>::iterator I;
    int cnt = 0;
    for (I = bb_blocks.begin(); I != bb_blocks.end(); I++) {
        gm_gps_basic_block* b = *I;
        if ((!b->is_prepare()) && (!b->is_vertex())) continue;
        int id = b->get_id();
        sprintf(temp, "case %d: _vertex_state_%d(_msgs); break;", id, id);
        Body.pushln(temp);
        cnt++;
    }
    if (cnt == 0) {
        Body.pushln("default: break;");
    }
    Body.pushln("}");

    Body.pushln("}");

    gm_redirect_reproduce(f_body);
    gm_baseindent_reproduce(3);
    for (I = bb_blocks.begin(); I != bb_blocks.end(); I++) {
        gm_gps_basic_block* b = *I;
        if ((!b->is_prepare()) && (!b->is_vertex())) continue;
        do_generate_vertex_state_body(b);
    }
    gm_redirect_reproduce(stdout);
    gm_baseindent_reproduce(0);

    Body.NL();
}
