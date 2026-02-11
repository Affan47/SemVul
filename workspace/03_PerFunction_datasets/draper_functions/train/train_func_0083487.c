gcr_renderer_default_init (GcrRendererIface *iface)
{
	static gboolean initialized = FALSE;
	if (!initialized) {


		g_object_interface_install_property (iface,
		         g_param_spec_string ("label", "Label", "The label for the renderer",
		                              "", G_PARAM_READWRITE));


		g_object_interface_install_property (iface,
		         g_param_spec_boxed ("attributes", "Attributes", "The data displayed in the renderer",
		                             GCK_TYPE_ATTRIBUTES, G_PARAM_READWRITE));


		signals[DATA_CHANGED] = g_signal_new ("data-changed", GCR_TYPE_RENDERER, G_SIGNAL_RUN_LAST,
		                                      G_STRUCT_OFFSET (GcrRendererIface, data_changed),
		                                      NULL, NULL, g_cclosure_marshal_VOID__VOID, G_TYPE_NONE, 0);

		initialized = TRUE;
	}
}
