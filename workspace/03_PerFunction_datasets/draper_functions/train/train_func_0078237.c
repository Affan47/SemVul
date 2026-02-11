recurrenceGetAccountPeriodValue(const Recurrence *r, Account *acc, guint n)
{
    time64 t1, t2;


    g_return_val_if_fail(r && acc, gnc_numeric_zero());
    t1 = recurrenceGetPeriodTime(r, n, FALSE);
    t2 = recurrenceGetPeriodTime(r, n, TRUE);
    return xaccAccountGetBalanceChangeForPeriod (acc, t1, t2, TRUE);
}
