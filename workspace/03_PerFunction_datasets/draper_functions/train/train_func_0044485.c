do_validate_scan() {
    DB_VALIDATOR_ITEM_SET validator;
    std::vector<VALIDATOR_ITEM> items;
    bool found=false;
    int retval, i=0;


    while (1) {
        retval = validator.enumerate(
            app.id, SELECT_LIMIT, wu_id_modulus, wu_id_remainder, items
        );
        if (retval) {
            if (retval != ERR_DB_NOT_FOUND) {
                log_messages.printf(MSG_DEBUG,
                    "DB connection lost, exiting\n"
                );
                exit(0);
            }
            break;
        }
        retval = handle_wu(validator, items);
        if (!retval) found = true;
        if (++i == one_pass_N_WU) break;
    }
    return found;
}
