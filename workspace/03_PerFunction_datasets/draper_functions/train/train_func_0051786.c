on_switch_page(GtkNotebook* nb, GtkWidget* page, gint num, AppChooserData* data)
{
    if(num == 0)
    {
        gtk_dialog_set_response_sensitive(data->dlg, GTK_RESPONSE_OK,
                        fm_app_menu_view_is_app_selected(data->apps_view));
    }
    else
    {
        const char* cmd = gtk_entry_get_text(data->cmdline);
        gtk_dialog_set_response_sensitive(data->dlg, GTK_RESPONSE_OK, (cmd && cmd[0]));
    }
}
