refresh_handler (GHashTable *changes, gpointer user_data)
{
    AccountWindow *aw = user_data;
    const EventInfo *info;
    Account *account;

    account = aw_get_account (aw);
    if (!account)
    {
        gnc_close_gui_component (aw->component_id);
        return;
    }

    if (changes)
    {
        info = gnc_gui_get_entity_events (changes, &aw->account);
        if (info && (info->event_mask & QOF_EVENT_DESTROY))
        {
            gnc_close_gui_component (aw->component_id);
            return;
        }
    }

    gnc_ui_refresh_account_window (aw);
}
