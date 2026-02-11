gnucash_sheet_set_window (GnucashSheet *sheet, GtkWidget *window)
{
    g_return_if_fail (sheet != NULL);
    g_return_if_fail (GNUCASH_IS_SHEET(sheet));

    if (window)
        g_return_if_fail (GTK_IS_WIDGET(window));

    sheet->window = window;
}
