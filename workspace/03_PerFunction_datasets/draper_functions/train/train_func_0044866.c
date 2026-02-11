on_rm(GtkAction* act, FmFolderView* fv)
{
    GtkMenu *popup = g_object_get_qdata(G_OBJECT(fv), popup_quark);
    GtkWidget *win = gtk_menu_get_attach_widget(popup);
    GtkWidget *focus = gtk_window_get_focus(GTK_WINDOW(win));


    if(FOCUS_IS_IN_FOLDER_VIEW(focus, GTK_WIDGET(fv)))
    {
        FmPathList* files = fm_folder_view_dup_selected_file_paths(fv);
        if(files)
        {
            fm_delete_files(GTK_WINDOW(win), files);
            fm_path_list_unref(files);
        }
    }

    else if(GTK_IS_EDITABLE(focus))
        gtk_editable_cut_clipboard((GtkEditable*)focus);
}
