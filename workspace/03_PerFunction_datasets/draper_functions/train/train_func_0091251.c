gnc_amount_edit_set_fraction (GNCAmountEdit *gae, int fraction)
{
    g_return_if_fail(gae != NULL);
    g_return_if_fail(GNC_IS_AMOUNT_EDIT(gae));

    fraction = MAX (0, fraction);

    gae->fraction = fraction;
}
