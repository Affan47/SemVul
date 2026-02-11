method_changed (GtkComboBox *combo, gpointer user_data)
{
	CEPageIP4Private *priv = CE_PAGE_IP4_GET_PRIVATE (user_data);
	guint32 method = IP4_METHOD_AUTO;
	gboolean addr_enabled = FALSE;
	gboolean dns_enabled = FALSE;
	gboolean dhcp_enabled = FALSE;
	gboolean routes_enabled = FALSE;
	gboolean ip4_required_enabled = TRUE;
	gboolean method_auto = FALSE;
	GtkTreeIter iter;

	if (gtk_combo_box_get_active_iter (priv->method, &iter)) {
		gtk_tree_model_get (GTK_TREE_MODEL (priv->method_store), &iter,
		                    METHOD_COL_NUM, &method, -1);
	}

	switch (method) {
	case IP4_METHOD_AUTO:
		addr_enabled = FALSE;
		dhcp_enabled = routes_enabled = TRUE;
		dns_enabled = TRUE;
		method_auto = TRUE;
		break;
	case IP4_METHOD_AUTO_ADDRESSES:
		addr_enabled = FALSE;
		dns_enabled = dhcp_enabled = routes_enabled = TRUE;
		break;
	case IP4_METHOD_MANUAL:
		addr_enabled = dns_enabled = routes_enabled = TRUE;
		break;
	case IP4_METHOD_DISABLED:
		addr_enabled = dns_enabled = dhcp_enabled = routes_enabled = ip4_required_enabled = FALSE;
	default:
		break;
	}


	if (   priv->connection_type == NM_TYPE_SETTING_VPN
	    || priv->connection_type == NM_TYPE_SETTING_GSM
	    || priv->connection_type == NM_TYPE_SETTING_CDMA
	    || priv->connection_type == NM_TYPE_SETTING_PPPOE)
		dhcp_enabled = FALSE;

	gtk_widget_set_sensitive (priv->addr_label, addr_enabled);
	gtk_widget_set_sensitive (GTK_WIDGET (priv->addr_add), addr_enabled);
	gtk_widget_set_sensitive (GTK_WIDGET (priv->addr_delete), addr_enabled);
	gtk_widget_set_sensitive (GTK_WIDGET (priv->addr_list), addr_enabled);
	if (!addr_enabled) {
		GtkListStore *store;

		store = GTK_LIST_STORE (gtk_tree_view_get_model (priv->addr_list));
		gtk_list_store_clear (store);
	}

	gtk_widget_set_sensitive (priv->dns_servers_label, dns_enabled);
	if (method_auto)
		gtk_label_set_text_with_mnemonic (GTK_LABEL (priv->dns_servers_label), _("Additional DNS ser_vers:"));
	else
		gtk_label_set_text_with_mnemonic (GTK_LABEL (priv->dns_servers_label), _("DNS ser_vers:"));
	gtk_widget_set_sensitive (GTK_WIDGET (priv->dns_servers), dns_enabled);
	if (!dns_enabled)
		gtk_entry_set_text (priv->dns_servers, "");

	gtk_widget_set_sensitive (priv->dns_searches_label, dns_enabled);
	if (method_auto)
		gtk_label_set_text_with_mnemonic (GTK_LABEL (priv->dns_searches_label), _("Additional s_earch domains:"));
	else
		gtk_label_set_text_with_mnemonic (GTK_LABEL (priv->dns_searches_label), _("S_earch domains:"));
	gtk_widget_set_sensitive (GTK_WIDGET (priv->dns_searches), dns_enabled);
	if (!dns_enabled)
		gtk_entry_set_text (priv->dns_searches, "");

	gtk_widget_set_sensitive (priv->dhcp_client_id_label, dhcp_enabled);
	gtk_widget_set_sensitive (GTK_WIDGET (priv->dhcp_client_id), dhcp_enabled);
	if (!dhcp_enabled)
		gtk_entry_set_text (priv->dhcp_client_id, "");

	gtk_widget_set_sensitive (GTK_WIDGET (priv->ip4_required), ip4_required_enabled);

	gtk_widget_set_sensitive (GTK_WIDGET (priv->routes_button), routes_enabled);

	ce_page_changed (CE_PAGE (user_data));
}
