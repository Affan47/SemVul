gnc_account_separator_is_valid (const gchar *separator,
                                              gchar **normalized_separator)
{
    QofBook *book = gnc_get_current_book();
    GList *conflict_accts = NULL;
    gchar *message = NULL;

    *normalized_separator = gnc_normalize_account_separator (separator);
    conflict_accts = gnc_account_list_name_violations (book, *normalized_separator);
    if (conflict_accts)
        message = gnc_account_name_violations_errmsg (*normalized_separator,
                                                      conflict_accts);

    g_list_free (conflict_accts);

    return message;
}
