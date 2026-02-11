glade_widget_adaptor_post_create (GladeWidgetAdaptor *adaptor,
				  GObject            *object,
				  GladeCreateReason   reason)
{
	g_return_if_fail (GLADE_IS_WIDGET_ADAPTOR (adaptor));
	g_return_if_fail (G_IS_OBJECT (object));
	g_return_if_fail (g_type_is_a (G_OBJECT_TYPE (object), adaptor->type));


	if (GLADE_WIDGET_ADAPTOR_GET_CLASS (adaptor)->deep_post_create)
		GLADE_WIDGET_ADAPTOR_GET_CLASS (adaptor)->deep_post_create (adaptor, object, reason);

	if (GLADE_WIDGET_ADAPTOR_GET_CLASS (adaptor)->post_create)
		GLADE_WIDGET_ADAPTOR_GET_CLASS (adaptor)->post_create (adaptor, object, reason);

}
