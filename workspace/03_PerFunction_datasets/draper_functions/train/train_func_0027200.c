gnc_bi_import_gui_option5_cb (GtkWidget *widget, gpointer data)
{
    BillImportGui *gui = data;
    gchar *temp;
    if (!gtk_toggle_button_get_active( GTK_TOGGLE_BUTTON(widget) ))
        return;
    temp = gnc_input_dialog (0, _("Adjust regular expression used for import"), _("This regular expression is used to parse the import file. Modify according to your needs.\n"), gui->regexp->str);
    if (temp)
    {
        g_string_assign (gui->regexp, temp);
        g_free (temp);
        gnc_bi_import_gui_filenameChanged_cb (gui->entryFilename, gui);
    }
}
