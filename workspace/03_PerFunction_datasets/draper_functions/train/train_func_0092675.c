glist_kvp_value_parser_new(sixtp *kvp_frame_parser)
{
    sixtp *top_level = sixtp_set_any(
                           sixtp_new(), FALSE,
                           SIXTP_CHARACTERS_HANDLER_ID, allow_and_ignore_only_whitespace,
                           SIXTP_END_HANDLER_ID, glist_kvp_value_end_handler,
                           SIXTP_CLEANUP_RESULT_ID, kvp_value_result_cleanup,
                           SIXTP_RESULT_FAIL_ID, kvp_value_result_cleanup,
                           SIXTP_NO_MORE_HANDLERS);
    if (!top_level)
    {
        return NULL;
    }

    if (!add_all_kvp_value_parsers_as_sub_nodes(top_level,
            kvp_frame_parser,
            top_level))
    {
        sixtp_destroy(top_level);
        return(NULL);
    }

    return(top_level);
}
