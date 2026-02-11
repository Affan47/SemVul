on_file_menu(GtkAction* act, FmFolderView* fv)
{
    FmFolderViewInterface *iface = FM_FOLDER_VIEW_GET_IFACE(fv);
    GtkMenu *popup;
    FmFileInfoList* files;
    GtkWindow *win;
    FmFolderViewUpdatePopup update_popup;
    FmLaunchFolderFunc open_folders;

    if(iface->count_selected_files(fv) > 0)
    {
        popup = g_object_get_qdata(G_OBJECT(fv), popup_quark);
        if(popup == NULL)
            return;
        files = iface->dup_selected_files(fv);
        win = GTK_WINDOW(gtk_menu_get_attach_widget(popup));
        iface->get_custom_menu_callbacks(fv, &update_popup, &open_folders);
        popup = _make_file_menu(fv, win, update_popup, open_folders, files);
        fm_file_info_list_unref(files);
        gtk_menu_popup(popup, NULL, NULL, popup_position_func, fv, 3,
                       gtk_get_current_event_time());
    }
}
