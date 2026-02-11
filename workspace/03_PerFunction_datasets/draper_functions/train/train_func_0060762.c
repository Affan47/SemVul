fm_launch_files_simple(GtkWindow* parent, GAppLaunchContext* ctx, GList* file_infos, FmLaunchFolderFunc func, gpointer user_data)
{
    FmFileLauncher launcher = {
        .get_app = choose_app,
        .open_folder = on_open_folder,
        .exec_file = on_exec_file,
        .error = on_launch_error,
        .ask = on_launch_ask
    };
    LaunchData data = {parent, func, user_data};
    GdkAppLaunchContext* _ctx = NULL;
    gboolean ret;

    if (!func)
        launcher.open_folder = NULL;

    if(ctx == NULL)
    {
        _ctx = gdk_display_get_app_launch_context(gdk_display_get_default());
        gdk_app_launch_context_set_screen(_ctx, parent ? gtk_widget_get_screen(GTK_WIDGET(parent)) : gdk_screen_get_default());
        gdk_app_launch_context_set_timestamp(_ctx, gtk_get_current_event_time());

        ctx = G_APP_LAUNCH_CONTEXT(_ctx);
    }
    ret = fm_launch_files(ctx, file_infos, &launcher, &data);
    if(_ctx)
        g_object_unref(_ctx);
    return ret;
}
