gtksharp_override_property_handlers(GType type, gpointer get_property_cb, gpointer set_property_cb)
{
	GObjectClass *type_class = g_type_class_peek (type);
	if(!type_class)
		type_class = g_type_class_ref (type);

	type_class->get_property = get_property_cb;
	type_class->set_property = set_property_cb;
}
