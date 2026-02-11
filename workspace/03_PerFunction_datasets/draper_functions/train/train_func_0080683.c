panel_lockdown_on_notify_notified (GObject    *gobject,
                                   GParamSpec *pspec,
                                   gpointer    user_data)
{
        PanelLockdownNotifyData *notify_data = user_data;

        g_assert (notify_data->callback != NULL);
        g_assert ((gpointer) notify_data->lockdown == (gpointer) gobject);

        notify_data->callback (notify_data->lockdown,
                               notify_data->callback_data);
}
