gnc_split_register_get_debcred_bg_color (VirtualLocation virt_loc,
        gboolean *hatching,
        gpointer user_data)
{
    SplitRegister *reg = user_data;

    if (hatching)
    {
        Transaction *trans;

        trans = gnc_split_register_get_trans (reg, virt_loc.vcell_loc);

        if (trans)
            *hatching = !xaccTransIsBalanced (trans);
        else
            *hatching = FALSE;
    }

    return gnc_split_register_get_bg_color (virt_loc, NULL, user_data);
}
