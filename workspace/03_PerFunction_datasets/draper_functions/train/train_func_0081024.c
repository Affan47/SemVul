gnc_bi_import_gui_buttonOpen_cb (GtkWidget *widget, gpointer data)
{
    gchar *filename;
    BillImportGui *gui = data;

    filename = gnc_plugin_bi_import_getFilename();
    if (filename)
    {

        gtk_entry_set_text( GTK_ENTRY(gui->entryFilename), filename );

        g_free( filename );
    }
}
