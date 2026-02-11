file_monitor_changed_cb (GFileMonitor *monitor,
                         GFile *file,
                         GFile *other_file,
                         GFileMonitorEvent event,
                         gpointer user_data)
{
    FontViewModel *self = user_data;

    if (event == G_FILE_MONITOR_EVENT_CHANGES_DONE_HINT ||
        event == G_FILE_MONITOR_EVENT_DELETED ||
        event == G_FILE_MONITOR_EVENT_CREATED)
        ensure_font_list (self);
}
