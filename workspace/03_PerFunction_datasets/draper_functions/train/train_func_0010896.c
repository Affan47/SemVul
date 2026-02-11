link_loss_register(struct btd_adapter *adapter, DBusConnection *conn)
{
	gboolean svc_added;
	bt_uuid_t uuid;
	struct link_loss_adapter *lladapter;

	bt_uuid16_create(&uuid, LINK_LOSS_SVC_UUID);

	lladapter = g_new0(struct link_loss_adapter, 1);
	lladapter->adapter = adapter;
	lladapter->conn = dbus_connection_ref(conn);

	link_loss_adapters = g_slist_append(link_loss_adapters, lladapter);


	svc_added = gatt_service_add(adapter,
			GATT_PRIM_SVC_UUID, &uuid,

			GATT_OPT_CHR_UUID, ALERT_LEVEL_CHR_UUID,
			GATT_OPT_CHR_PROPS,
				ATT_CHAR_PROPER_READ | ATT_CHAR_PROPER_WRITE,
			GATT_OPT_CHR_VALUE_CB, ATTRIB_READ,
				link_loss_alert_lvl_read, lladapter,
			GATT_OPT_CHR_VALUE_CB, ATTRIB_WRITE,
				link_loss_alert_lvl_write, lladapter,
			GATT_OPT_CHR_VALUE_GET_HANDLE,
				&lladapter->alert_lvl_value_handle,
			GATT_OPT_INVALID);

	if (!svc_added)
		goto err;

	DBG("Link Loss service added");
	return;

err:
	error("Error adding Link Loss service");
	link_loss_unregister(adapter);
}
