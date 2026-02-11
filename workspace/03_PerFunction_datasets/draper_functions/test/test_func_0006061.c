request_reread_prefs() {
    int retval;
    APP_INIT_DATA aid;

    link_user_files();

    init_app_init_data(aid);
    retval = write_app_init_file(aid);
    if (retval) return retval;
#if 0
    graphics_request_queue.msg_queue_send(
        xml_graphics_modes[MODE_REREAD_PREFS],
        app_client_shm.shm->graphics_request
    );
#endif
    return 0;
}
