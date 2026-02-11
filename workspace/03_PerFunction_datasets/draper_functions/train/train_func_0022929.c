gnc_popup_entry_set_text (GncPopupEntry *popup, const gchar *text)
{
    g_return_if_fail (GNC_IS_POPUP_ENTRY (popup));

    gtk_entry_set_text (GTK_ENTRY (popup->entry), text ? text : "");
}
