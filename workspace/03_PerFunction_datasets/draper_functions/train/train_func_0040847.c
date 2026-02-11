gtv_sr_get_imbalance (Transaction *trans)
{
    int i;
    Split *split = NULL;
    const gchar *acc_name;
    const gchar *prefix = _("Imbalance");

    for (i = 0; (split = xaccTransGetSplit (trans, i)); i++)
    {
        if (xaccSplitGetAccount (split) != NULL)
        {
            acc_name = xaccAccountGetName (xaccSplitGetAccount (split));

            if (g_str_has_prefix (acc_name, prefix))
                return TRUE;
        }
    }
    return FALSE;
}
