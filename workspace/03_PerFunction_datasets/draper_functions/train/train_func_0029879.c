gnc_split_register_get_mxfrm_help (VirtualLocation virt_loc,
                                   gpointer user_data)
{
    const char *help;

    SplitRegister *reg = user_data;
    Split *split;
    Split *s;

    split = gnc_split_register_get_split (reg, virt_loc.vcell_loc);
    if (!split)
        return NULL;

    s = xaccSplitGetOtherSplit (split);

    if (s)
    {
        help = gnc_split_register_get_mxfrm_entry (virt_loc, FALSE,
                NULL, user_data);
        if (!help || *help == '\0')
            help = _("Enter the account to transfer from, "
                     "or choose one from the list");
    }
    else
    {


        s = xaccTransGetSplit (xaccSplitGetParent(split), 1);

        if (s)
            help = _("This transaction has multiple splits; "
                     "press the Split button to see them all");
        else if (g_strcmp0 ("stock-split", xaccSplitGetType (split)) == 0)
            help = _("This transaction is a stock split; "
                     "press the Split button to see details");
        else
            help = "";
    }

    return g_strdup (help);
}
