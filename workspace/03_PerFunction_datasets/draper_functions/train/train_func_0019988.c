migrate_openvpn_secrets (const char *name, const char *uuid)
{
	int status;
	GList *list = NULL;
	GList *iter;

	status = gnome_keyring_find_network_password_sync (g_get_user_name (),
	                                                   NULL,
	                                                   name,
	                                                   NULL,
	                                                   "org.freedesktop.NetworkManager.openvpn",
	                                                   NULL,
	                                                   0,
	                                                   &list);
	if (status != GNOME_KEYRING_RESULT_OK || !g_list_length (list))
		return;


	for (iter = list; iter; iter = iter->next) {
		GnomeKeyringNetworkPasswordData *found = iter->data;


		if (strcmp (found->keyring, "session") != 0)
			nm_gconf_add_keyring_item (uuid, name, NM_SETTING_VPN_SETTING_NAME, found->object, found->password);

		gnome_keyring_item_delete_sync (found->keyring, found->item_id);
	}

	gnome_keyring_network_password_list_free (list);
}
