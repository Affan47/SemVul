request_reread_app_info() {
    APP_INIT_DATA aid;
    init_app_init_data(aid);
    int retval = write_app_init_file(aid);
    if (retval) return retval;
    process_control_queue.msg_queue_send(
        "<reread_app_info/>",
        app_client_shm.shm->process_control_request
    );
    return 0;
}
