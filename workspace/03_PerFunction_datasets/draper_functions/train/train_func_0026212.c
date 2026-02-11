jaw_impl_get_type (guint tflag)
{
	GType type;

	static const GInterfaceInfo atk_action_info =
	{
		(GInterfaceInitFunc) jaw_action_interface_init,
		(GInterfaceFinalizeFunc) NULL,
		NULL
	};

	static const GInterfaceInfo atk_component_info =
	{
		(GInterfaceInitFunc) jaw_component_interface_init,
		(GInterfaceFinalizeFunc) NULL,
		NULL
	};

	static const GInterfaceInfo atk_text_info =
	{
		(GInterfaceInitFunc) jaw_text_interface_init,
		(GInterfaceFinalizeFunc) NULL,
		NULL
	};

	static const GInterfaceInfo atk_editable_text_info =
	{
		(GInterfaceInitFunc) jaw_editable_text_interface_init,
		(GInterfaceFinalizeFunc) NULL,
		NULL
	};

	static const GInterfaceInfo atk_hypertext_info =
	{
		(GInterfaceInitFunc) jaw_hypertext_interface_init,
		(GInterfaceFinalizeFunc) NULL,
		NULL
	};

	static const GInterfaceInfo atk_image_info =
	{
		(GInterfaceInitFunc) jaw_image_interface_init,
		(GInterfaceFinalizeFunc) NULL,
		NULL
	};

	static const GInterfaceInfo atk_selection_info =
	{
		(GInterfaceInitFunc) jaw_selection_interface_init,
		(GInterfaceFinalizeFunc) NULL,
		NULL
	};

	static const GInterfaceInfo atk_value_info =
	{
		(GInterfaceInitFunc) jaw_value_interface_init,
		(GInterfaceFinalizeFunc) NULL,
		NULL
	};

	static const GInterfaceInfo atk_table_info =
	{
		(GInterfaceInitFunc) jaw_table_interface_init,
		(GInterfaceFinalizeFunc) NULL,
		NULL
	};

	if (typeTable == NULL) {
		typeTable = g_hash_table_new( NULL, NULL );
	}

	type = (GType)g_hash_table_lookup(typeTable, (gpointer)tflag);
	if (type == 0) {
		GTypeInfo tinfo = {
			sizeof(JawImplClass),
			(GBaseInitFunc) NULL,
			(GBaseFinalizeFunc) NULL,
			(GClassInitFunc) jaw_impl_class_intern_init,
			(GClassFinalizeFunc) NULL,
			NULL,
			sizeof(JawImpl),
			0,
			(GInstanceInitFunc) NULL,
			NULL
		};

		gchar className[20];
		g_sprintf(className, "JawImpl_%d", tflag);

		type = g_type_register_static(JAW_TYPE_OBJECT,
				className, &tinfo, 0);

		if (tflag & INTERFACE_ACTION) {
			g_type_add_interface_static (type, ATK_TYPE_ACTION,
						&atk_action_info);
		}

		if (tflag & INTERFACE_COMPONENT) {
			g_type_add_interface_static (type, ATK_TYPE_COMPONENT,
						&atk_component_info);
		}

		if (tflag & INTERFACE_TEXT) {
			g_type_add_interface_static (type, ATK_TYPE_TEXT,
						&atk_text_info);
		}

		if (tflag & INTERFACE_EDITABLE_TEXT) {
			g_type_add_interface_static (type, ATK_TYPE_EDITABLE_TEXT,
						&atk_editable_text_info);
		}

		if (tflag & INTERFACE_HYPERTEXT) {
			g_type_add_interface_static (type, ATK_TYPE_HYPERTEXT,
						&atk_hypertext_info);
		}

		if (tflag & INTERFACE_IMAGE) {
			g_type_add_interface_static (type, ATK_TYPE_IMAGE,
						&atk_image_info);
		}

		if (tflag & INTERFACE_SELECTION) {
			g_type_add_interface_static (type, ATK_TYPE_SELECTION,
						&atk_selection_info);
		}

		if (tflag & INTERFACE_VALUE) {
			g_type_add_interface_static (type, ATK_TYPE_VALUE,
						&atk_value_info);
		}

		if (tflag & INTERFACE_TABLE) {
			g_type_add_interface_static (type, ATK_TYPE_TABLE,
						&atk_table_info);
		}

		g_hash_table_insert(typeTable, (gpointer)tflag, (gpointer)type);
	}

	return type;
}
