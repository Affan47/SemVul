midgard_core_dbus_send_serialized_object(MidgardObject *object, const gchar *path)
{
#ifdef MGD_HAVE_DBUS
	g_assert(object != NULL);
	g_assert(path != NULL);

	gchar *xml = midgard_replicator_serialize(G_OBJECT(object));

	midgard_dbus_send(MGD_OBJECT_CNC(object), path, xml, FALSE);

	g_free(xml);
#endif
	return;
}
