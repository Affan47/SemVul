notify_save_hotkeys(PrefsPage *page)
{
    const gchar *tmp_str;
    notify_config.hotkeys_enabled = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(hotkeys_page.hotkeys_enabled));

    tmp_str = gtk_entry_get_text(GTK_ENTRY(hotkeys_page.hotkeys_toggle_mainwindow));
    if(notify_config.hotkeys_toggle_mainwindow)
      g_free(notify_config.hotkeys_toggle_mainwindow);
    notify_config.hotkeys_toggle_mainwindow = g_strdup(tmp_str);

    notification_hotkeys_update_bindings();
}
