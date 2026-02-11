afr_changelog_post_op_call_count (afr_transaction_type type,
                                  unsigned char *pre_op,
                                  unsigned int child_count)
{
        int           call_count = 0;

        call_count = afr_pre_op_done_children_count (pre_op, child_count);
        if (type == AFR_ENTRY_RENAME_TRANSACTION)
                call_count *= 2;

        return call_count;
}
