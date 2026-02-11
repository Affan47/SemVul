bluetooth_chooser_class_init (BluetoothChooserClass *klass)
{


	guint i;
	int max_filter_val;

	bind_textdomain_codeset(GETTEXT_PACKAGE, "UTF-8");

	g_type_class_add_private(klass, sizeof(BluetoothChooserPrivate));

	G_OBJECT_CLASS(klass)->constructor = bluetooth_chooser_constructor;
	G_OBJECT_CLASS(klass)->finalize = bluetooth_chooser_finalize;

	G_OBJECT_CLASS(klass)->set_property = bluetooth_chooser_set_property;
	G_OBJECT_CLASS(klass)->get_property = bluetooth_chooser_get_property;


	selection_table_signals[SELECTED_DEVICE_CHANGED] =
		g_signal_new ("selected-device-changed",
			      G_TYPE_FROM_CLASS (klass),
			      G_SIGNAL_RUN_LAST,
			      G_STRUCT_OFFSET (BluetoothChooserClass, selected_device_changed),
			      NULL, NULL,
			      g_cclosure_marshal_VOID__STRING,
			      G_TYPE_NONE, 1, G_TYPE_STRING);


	selection_table_signals[SELECTED_DEVICE_ACTIVATED] =
		g_signal_new ("selected-device-activated",
			      G_TYPE_FROM_CLASS (klass),
			      G_SIGNAL_RUN_LAST,
			      G_STRUCT_OFFSET (BluetoothChooserClass, selected_device_activated),
			      NULL, NULL,
			      g_cclosure_marshal_VOID__STRING,
			      G_TYPE_NONE, 1, G_TYPE_STRING);

	g_object_class_install_property (G_OBJECT_CLASS(klass),
					 PROP_DEVICE_SELECTED, g_param_spec_string ("device-selected",
										    "device-selected", "The Bluetooth address for the currently selected device, or %NULL", NULL, G_PARAM_READABLE | G_PARAM_WRITABLE));
	g_object_class_install_property (G_OBJECT_CLASS(klass),
					 PROP_SHOW_PAIRING, g_param_spec_boolean ("show-pairing",
										  "show-pairing", "Whether to show the pairing column in the tree.", FALSE, G_PARAM_READWRITE));
	g_object_class_install_property (G_OBJECT_CLASS(klass),
					 PROP_SHOW_CONNECTED, g_param_spec_boolean ("show-connected",
										    "show-connected", "Whether to show the connected column in the tree.", FALSE, G_PARAM_READWRITE));
	g_object_class_install_property (G_OBJECT_CLASS(klass),
					 PROP_SHOW_SEARCHING, g_param_spec_boolean ("show-searching",
										    "show-searching",
										    "Whether to show the Searching label , this is necessary if you want to programmatically start a discovery, using bluetooth_chooser_start_discovery()",
										    FALSE, G_PARAM_READWRITE));
	g_object_class_install_property (G_OBJECT_CLASS(klass),
					 PROP_SHOW_DEVICE_TYPE, g_param_spec_boolean ("show-device-type",
										      "show-device-type", "Whether to show the device type filter", TRUE, G_PARAM_READWRITE | G_PARAM_CONSTRUCT));
	g_object_class_install_property (G_OBJECT_CLASS(klass),
					 PROP_SHOW_DEVICE_TYPE_COLUMN, g_param_spec_boolean ("show-device-type-column",
											     "show-device-type-column", "Whether to show the device type column", TRUE, G_PARAM_READWRITE | G_PARAM_CONSTRUCT));
	g_object_class_install_property (G_OBJECT_CLASS(klass),
					 PROP_SHOW_DEVICE_CATEGORY, g_param_spec_boolean ("show-device-category",
											  "show-device-category", "Whether to show the device category filter", TRUE, G_PARAM_READWRITE | G_PARAM_CONSTRUCT));
	for (i = 0, max_filter_val = 0 ; i < _BLUETOOTH_TYPE_NUM_TYPES; i++)
		max_filter_val += 1 << i;
	g_object_class_install_property (G_OBJECT_CLASS(klass),
					 PROP_DEVICE_TYPE_FILTER, g_param_spec_int ("device-type-filter",
										    "device-type-filter", "A bitmask of #BluetoothType to show", BLUETOOTH_TYPE_ANY, max_filter_val, 1, G_PARAM_READWRITE | G_PARAM_CONSTRUCT));
	g_object_class_install_property (G_OBJECT_CLASS(klass),
					 PROP_DEVICE_CATEGORY_FILTER, g_param_spec_enum ("device-category-filter",
											 "device-category-filter", "The #BluetoothCategory to show", BLUETOOTH_TYPE_CATEGORY, BLUETOOTH_CATEGORY_ALL, G_PARAM_READWRITE | G_PARAM_CONSTRUCT));
	g_object_class_install_property (G_OBJECT_CLASS(klass),
					 PROP_DEVICE_SERVICE_FILTER, g_param_spec_string ("device-service-filter",
											  "device-service-filter", "A string representing the service to filter for", NULL, G_PARAM_WRITABLE));
	g_object_class_install_property (G_OBJECT_CLASS(klass),
					 PROP_INTERNAL_FILTER, g_param_spec_boolean ("has-internal-device-filter",
											  "has-internal-device-filter", "Whether the #BluetoothChooser should be constructed with a visible #BluetoothFilterWidget", TRUE, G_PARAM_CONSTRUCT_ONLY | G_PARAM_READWRITE));
}
