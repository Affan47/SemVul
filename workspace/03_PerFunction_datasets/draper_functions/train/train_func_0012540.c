select_share_path_clicked(struct w *widgets)
{
    gchar *path = NULL, *sharesdir = NULL;

    sharesdir = g_strdup_printf("%s/lib/samba", LOCALSTATEDIR);

    path = get_dialog_path_selection("DIR", sharesdir, "None");
    if( path!=NULL )
    {
        printf("Selected directory: %s\n", path);
        gtk_entry_set_text(GTK_ENTRY(widgets->share_set_entry[1]), path);
        g_free(path);
    }

    g_free(sharesdir);
}
