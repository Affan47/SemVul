gnc_stock_split_assistant_view_filter_asset (Account  *account,
        gpointer  data)
{
    GNCAccountType type;

    type = xaccAccountGetType(account);
    return ((type == ACCT_TYPE_BANK) || (type == ACCT_TYPE_CASH) ||
            (type == ACCT_TYPE_ASSET));
}
