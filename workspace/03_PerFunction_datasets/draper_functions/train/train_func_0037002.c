check_update(GBDATA *) {
    GB_transaction ta(gb_main);

    const SEC_db_interface *db = sec_root->get_db();

    if (db && db->canDisplay()) {
        if (update_requested & SEC_UPDATE_RELOAD) {
            GB_ERROR error   = load(0, 0, 0, 0);
            if (error) {
                error = ta.close(error);
                aw_message(error);
            }

            update_requested = static_cast<SEC_update_request>((update_requested^SEC_UPDATE_RELOAD)|SEC_UPDATE_RECOUNT);
            exports.refresh  = 1;
        }

        if (update_requested & SEC_UPDATE_SHOWN_POSITIONS) {
            sec_root->update_shown_positions();
            update_requested = static_cast<SEC_update_request>((update_requested^SEC_UPDATE_SHOWN_POSITIONS)|SEC_UPDATE_RECOUNT);
            exports.refresh  = 1;
        }

        if (update_requested & SEC_UPDATE_RECOUNT) {
            sec_root->invalidate_base_positions();
            sec_root->relayout();

            update_requested = static_cast<SEC_update_request>(update_requested^SEC_UPDATE_RECOUNT);
            exports.refresh  = 1;
        }

        sec_root->perform_autoscroll();
    }

    int res = 0;
    if (update_requested & SEC_UPDATE_ZOOM_RESET) {
        res              = 1;
        update_requested = static_cast<SEC_update_request>(update_requested^SEC_UPDATE_ZOOM_RESET);
    }
    return res;
}
