gnc_budget_is_account_period_value_set(const GncBudget *budget, const Account *account,
                                       guint period_num)
{
    gchar path[BUF_SIZE];
    gchar *bufend;
    KvpFrame *frame;

    g_return_val_if_fail(GNC_IS_BUDGET(budget), FALSE);
    g_return_val_if_fail(account, FALSE);

    frame = qof_instance_get_slots(QOF_INSTANCE(budget));
    bufend = guid_to_string_buff(xaccAccountGetGUID(account), path);
    g_sprintf(bufend, "/%d", period_num);
    return (kvp_frame_get_value(frame, path) != NULL);
}
