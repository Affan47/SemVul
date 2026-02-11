gnc_ab_get_purpose(const AB_TRANSACTION *ab_trans)
{
    const GWEN_STRINGLIST *ab_purpose;
    gchar *gnc_description = NULL;

    g_return_val_if_fail(ab_trans, g_strdup(""));

    ab_purpose = AB_Transaction_GetPurpose(ab_trans);
    if (ab_purpose)
        GWEN_StringList_ForEach(ab_purpose, join_ab_strings_cb,
                                &gnc_description);

    if (!gnc_description)
        gnc_description = g_strdup("");

    return gnc_description;
}
