gnc_txn_restore_split_parser_new(void)
{
    sixtp *top_level;

    if (!(top_level =
                sixtp_set_any(sixtp_new(), FALSE,
                              SIXTP_START_HANDLER_ID, txn_restore_split_start_handler,
                              SIXTP_CHARACTERS_HANDLER_ID,
                              allow_and_ignore_only_whitespace,
                              SIXTP_END_HANDLER_ID, txn_restore_split_end_handler,
                              SIXTP_FAIL_HANDLER_ID, txn_restore_split_fail_handler,
                              SIXTP_AFTER_CHILD_HANDLER_ID,
                              txn_restore_split_after_child_handler,
                              SIXTP_NO_MORE_HANDLERS)))
    {
        return NULL;
    }

    if (!sixtp_add_some_sub_parsers(
                top_level, TRUE,
                "guid", restore_char_generator(txn_restore_split_guid_end_handler),
                "memo", restore_char_generator(txn_restore_split_memo_end_handler),
                "action",
                restore_char_generator(txn_restore_split_action_end_handler),
                "account",
                restore_char_generator(txn_restore_split_account_end_handler),
                "reconcile-state",
                restore_char_generator(txn_restore_split_reconcile_state_end_handler),
                "reconcile-date",
                generic_timespec_parser_new(
                    txn_restore_split_reconcile_date_end_handler),
                "quantity", generic_gnc_numeric_parser_new(),
                "value", generic_gnc_numeric_parser_new(),
                "slots", kvp_frame_parser_new(),
                NULL, NULL))
    {
        return NULL;
    }

    return(top_level);
}
