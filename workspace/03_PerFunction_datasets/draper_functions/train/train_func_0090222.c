gnc_account_parser_new(void)
{
    sixtp *restore_pr;
    sixtp *ret;


    if (!(ret = sixtp_set_any(
                    sixtp_new(), FALSE,
                    SIXTP_START_HANDLER_ID, account_start_handler,
                    SIXTP_CHARACTERS_HANDLER_ID, allow_and_ignore_only_whitespace,
                    SIXTP_NO_MORE_HANDLERS)))
    {
        return NULL;
    }


    if (!(restore_pr =
                sixtp_set_any(sixtp_new(), FALSE,
                              SIXTP_START_HANDLER_ID, account_restore_start_handler,
                              SIXTP_END_HANDLER_ID, account_restore_end_handler,
                              SIXTP_FAIL_HANDLER_ID, account_restore_fail_handler,
                              SIXTP_AFTER_CHILD_HANDLER_ID,
                              account_restore_after_child_handler,
                              SIXTP_NO_MORE_HANDLERS)))
    {
        sixtp_destroy(ret);
        return NULL;
    }


    if (!sixtp_add_some_sub_parsers(
                restore_pr, TRUE,
                "name", restore_char_generator(acc_restore_name_end_handler),
                "guid", restore_char_generator(acc_restore_guid_end_handler),
                "type", restore_char_generator(acc_restore_type_end_handler),
                "code", restore_char_generator(acc_restore_code_end_handler),
                "description",
                restore_char_generator(acc_restore_description_end_handler),
                "notes", restore_char_generator(acc_restore_notes_end_handler),

                "currency", generic_gnc_commodity_lookup_parser_new(),

                "security", generic_gnc_commodity_lookup_parser_new(),

                "parent", sixtp_add_some_sub_parsers(
                    parent_lookup_parser_new(), TRUE,
                    "guid", generic_guid_parser_new(),
                    NULL, NULL),
                "slots", kvp_frame_parser_new(),
                NULL, NULL))
    {
        sixtp_destroy(ret);
        return NULL;
    }

    sixtp_add_sub_parser(ret, "restore", restore_pr);

    return ret;
}
