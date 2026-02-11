source_set_dbus_object (ESource *source,
                        EDBusObject *dbus_object)
{

	if (dbus_object == NULL)
		return;

	g_return_if_fail (E_DBUS_IS_OBJECT (dbus_object));
	g_return_if_fail (source->priv->dbus_object == NULL);

	source->priv->dbus_object = g_object_ref (dbus_object);
}
