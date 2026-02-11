gamt_rebuild_hosts(struct gamt_window *gamt)
{
    int count, size, pos;
    char *hosts_xml, *host, action[128];
    GtkActionEntry entry;
    GError *err = NULL;


    if (gamt->hosts_id) {
	gtk_ui_manager_remove_ui(gamt->ui, gamt->hosts_id);
	gamt->hosts_id = 0;
    }
    if (gamt->hosts_ag) {
	gtk_ui_manager_remove_action_group(gamt->ui, gamt->hosts_ag);
	g_object_unref(gamt->hosts_ag);
	gamt->hosts_ag = NULL;
    }


    memset(&entry, 0, sizeof(entry));
    entry.callback = G_CALLBACK(menu_cb_connect_to);
    gamt->hosts_ag = gtk_action_group_new("HostActions");
    count = cfg_entries_count("config", "hosts");
    size = 128 * count + sizeof(hosts_xml_start) + sizeof(hosts_xml_end);
    hosts_xml = malloc(size); pos = 0;
    pos += sprintf(hosts_xml+pos, "%s", hosts_xml_start);
    for (host = cfg_entries_first("config", "hosts");
	 NULL != host;
	 host = cfg_entries_next("config", "hosts", host)) {
	snprintf(action, sizeof(action), "ConnectTo_%s", host);
	pos += snprintf(hosts_xml+pos, 128,
			"      <menuitem action='%s'/>\n",
			action);
	entry.name = action;
	entry.label = host;
	gtk_action_group_add_actions(gamt->hosts_ag, &entry, 1, gamt);
    }
    pos += sprintf(hosts_xml+pos, "%s", hosts_xml_end);


    gtk_ui_manager_insert_action_group(gamt->ui, gamt->hosts_ag, 1);
    gamt->hosts_id = gtk_ui_manager_add_ui_from_string(gamt->ui, hosts_xml, -1, &err);
    if (!gamt->hosts_id) {
	g_message("building host menu failed: %s", err->message);
	g_error_free(err);
    }
}
