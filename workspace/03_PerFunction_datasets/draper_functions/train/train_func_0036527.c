commodity_restore_parser_new(void)
{
    sixtp *top_level;
    sixtp *restore_pr;

    top_level = sixtp_new();
    g_return_val_if_fail(top_level, NULL);

    if (!(restore_pr = sixtp_set_any(
                           sixtp_new(), FALSE,
                           SIXTP_START_HANDLER_ID, commodity_restore_start_handler,
                           SIXTP_END_HANDLER_ID, commodity_restore_end_handler,
                           SIXTP_FAIL_HANDLER_ID, generic_free_data_for_children,
                           SIXTP_AFTER_CHILD_HANDLER_ID, commodity_restore_after_child_handler,
                           SIXTP_NO_MORE_HANDLERS)))
    {
        sixtp_destroy(top_level);
        return(NULL);
    }
    sixtp_add_sub_parser(top_level, "restore", restore_pr);

    if (!sixtp_add_some_sub_parsers(
                restore_pr, TRUE,
                "space", simple_chars_only_parser_new(NULL),
                "id", simple_chars_only_parser_new(NULL),
                "name", simple_chars_only_parser_new(NULL),
                "xcode", simple_chars_only_parser_new(NULL),
                "fraction", simple_chars_only_parser_new(NULL),
                NULL, NULL))
    {
        return NULL;
    }

    return(top_level);
}
