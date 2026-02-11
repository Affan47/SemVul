char_discovered_cb(GSList *characteristics, guint8 status,
							gpointer user_data)
{
	DBusMessage *reply;
	struct query_data *current = user_data;
	struct gatt_service *gatt = current->gatt;
	struct gatt_primary *prim = gatt->prim;
	uint16_t *previous_end = NULL;
	GSList *l;
	bdaddr_t sba, dba;
	uint8_t bdaddr_type;

	if (status != 0) {
		const char *str = att_ecode2str(status);

		DBG("Discover all characteristics failed: %s", str);
		reply = btd_error_failed(gatt->query->msg, str);
		goto fail;
	}

	for (l = characteristics; l; l = l->next) {
		struct gatt_char *current_chr = l->data;
		struct characteristic *chr;
		guint handle = current_chr->value_handle;
		GSList *lchr;

		lchr = g_slist_find_custom(gatt->chars,
			GUINT_TO_POINTER(handle), characteristic_handle_cmp);
		if (lchr)
			continue;

		chr = g_new0(struct characteristic, 1);
		chr->gatt = gatt;
		chr->perm = current_chr->properties;
		chr->handle = current_chr->value_handle;
		strncpy(chr->type, current_chr->uuid, sizeof(chr->type));

		if (previous_end)
			*previous_end = current_chr->handle;

		previous_end = &chr->end;

		gatt->chars = g_slist_append(gatt->chars, chr);
		register_characteristic(chr, gatt->path);
	}

	if (previous_end)
		*previous_end = prim->range.end;

	gatt_get_address(gatt, &sba, &dba, &bdaddr_type);
	store_characteristics(&sba, &dba, bdaddr_type, prim->range.start,
								gatt->chars);

	g_slist_foreach(gatt->chars, update_all_chars, gatt);

	reply = create_discover_char_reply(gatt->query->msg, gatt->chars);

fail:
	dbus_message_unref(gatt->query->msg);
	gatt->query->msg = NULL;

	g_dbus_send_message(gatt->conn, reply);
	query_list_remove(gatt, current);
	g_free(current);
}
