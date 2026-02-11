on_delete(GtkAction* action, gpointer user_data)
{
    FmFileMenu* data = (FmFileMenu*)user_data;
    FmPathList* files;
    GtkWindow *window = GTK_WINDOW(gtk_menu_get_attach_widget(data->menu));

    files = fm_path_list_new_from_file_info_list(data->file_infos);

    if (!data->can_trash || data->shift_pressed)
        fm_delete_files(window, files);
    else
        fm_trash_or_delete_files(window, files);
    fm_path_list_unref(files);
}
