up_qos_name_owner_changed_cb (DBusGProxy *proxy, const gchar *name, const gchar *prev, const gchar *new, UpQos *qos)
{
	if (strlen (new) == 0)
		up_qos_remove_dbus (qos, name);
}
