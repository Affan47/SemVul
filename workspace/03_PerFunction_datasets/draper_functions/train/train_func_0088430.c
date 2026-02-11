fm_clipboard_paste_files(GtkWidget* dest_widget, FmPath* dest_dir)
{
    GdkDisplay* dpy = dest_widget ? gtk_widget_get_display(dest_widget) : gdk_display_get_default();
    GtkClipboard* clip = gtk_clipboard_get_for_display(dpy, GDK_SELECTION_CLIPBOARD);
    FmPathList* files;
    char** uris;
    int type = 0;
    GdkAtom *avail_targets;
    int n, i;
    gboolean _is_cut;


    if( !gtk_clipboard_wait_for_targets(clip, &avail_targets, &n) )
        return FALSE;


    check_atoms();
    for(i = 0; i < n; ++i)
    {
        if(avail_targets[i] == target_atom[GNOME_COPIED_FILES])
        {
            type = GNOME_COPIED_FILES;
            break;
        }
    }
    if( 0 == type )
    {

        for(i = 0; i < n; ++i)
        {
            if(avail_targets[i] == target_atom[URI_LIST])
            {
                type = URI_LIST;
                break;
            }
        }
        if( 0 == type )
        {

            for(i = 0; i < n; ++i)
            {
                if(avail_targets[i] == target_atom[UTF8_STRING])
                {
                    type = UTF8_STRING;
                    break;
                }
            }
        }
    }
    g_free(avail_targets);

    if( type )
    {
        GtkSelectionData* data;
        const gchar* pdata;
        gint length;

        data = gtk_clipboard_wait_for_contents(clip, target_atom[type]);
        pdata = (const gchar*)gtk_selection_data_get_data_with_length(data, &length);
        _is_cut = FALSE;

        switch(type)
        {
        case GNOME_COPIED_FILES:
            _is_cut = g_str_has_prefix(pdata, "cut\n");
            while(length)
            {
                register gchar ch = *pdata++;
                length--;
                if(ch == '\n')
                    break;
            }
            uris = g_uri_list_extract_uris(pdata);
            break;
        case URI_LIST:
            uris = g_uri_list_extract_uris(pdata);
            _is_cut = check_kde_curselection(clip);
            break;
        case UTF8_STRING:
        default:


            uris = g_uri_list_extract_uris(pdata);
            break;
        }
        gtk_selection_data_free(data);

        if(uris)
        {
            GtkWidget* parent;
            if(dest_widget)
                parent = gtk_widget_get_toplevel(dest_widget);
            else
                parent = NULL;

            files = fm_path_list_new_from_uris(uris);
            g_strfreev(uris);

            if(!fm_path_list_is_empty(files))
            {
                if( _is_cut )
                    fm_move_files(GTK_WINDOW(parent), files, dest_dir);
                else
                    fm_copy_files(GTK_WINDOW(parent), files, dest_dir);
            }
            fm_path_list_unref(files);
            return TRUE;
        }
    }
    return FALSE;
}
