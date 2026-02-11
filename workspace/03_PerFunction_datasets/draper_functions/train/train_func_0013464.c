fm_app_menu_view_dup_selected_app(GtkTreeView* view)
{
    char* id = fm_app_menu_view_dup_selected_app_desktop_id(view);
    if(id)
    {
        GDesktopAppInfo* app = g_desktop_app_info_new(id);
        g_free(id);
        return G_APP_INFO(app);
    }
    return NULL;
}
