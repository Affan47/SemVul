gnc_account_separator_validate_cb (GtkEntry *entry, GdkEvent *event, GtkWidget *dialog)
{
    gchar *separator;
    gchar *conflict_msg = gnc_account_separator_is_valid (gtk_entry_get_text (entry), &separator);


    if (conflict_msg)
    {
        gnc_warning_dialog(dialog, "%s", conflict_msg);
        g_free ( conflict_msg );
    }
    g_free (separator);
    return FALSE;
}
