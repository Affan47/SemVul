gnc_ui_owner_get_balance_full (GncOwner *owner,
                               gboolean *negative,
                               const gnc_commodity *commodity)
{
    gnc_numeric balance;

    if (!owner)
        return gnc_numeric_zero ();

    balance = gncOwnerGetBalanceInCurrency (owner, commodity);


    if ((gncOwnerGetType (owner) != GNC_OWNER_CUSTOMER))
        balance = gnc_numeric_neg (balance);


    if (negative)
        *negative = gnc_numeric_negative_p (balance);

    return balance;
}
