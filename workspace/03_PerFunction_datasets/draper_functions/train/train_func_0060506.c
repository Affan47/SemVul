got_http_error() {

    if (working_proxy_info.autodetect_proxy_supported) {
        working_proxy_info.need_autodetect_proxy_settings = true;
        working_proxy_info.have_autodetect_proxy_settings = false;
    }

    if (gstate.lookup_website_op.error_num == ERR_IN_PROGRESS) return;


    if (need_physical_connection) return;

    if (config.dont_contact_ref_site) return;

    if (log_flags.network_status_debug) {
        msg_printf(0, MSG_INFO,
            "[network_status] got HTTP error - checking ref site"
        );
    }
    need_to_contact_reference_site = true;
    show_ref_message = true;
}
