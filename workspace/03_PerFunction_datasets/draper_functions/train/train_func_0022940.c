xaccAccountSetAutoInterestXfer (Account *acc, gboolean option)
{
    if (!acc) return;

    xaccAccountBeginEdit (acc);

    kvp_frame_set_string (acc->inst.kvp_data,
                          "/reconcile-info/auto-interest-transfer",
                          (option ? "true" : "false"));
    mark_account (acc);
    xaccAccountCommitEdit (acc);
}
