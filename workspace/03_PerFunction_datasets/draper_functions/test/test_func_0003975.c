gal_a11y_e_table_get_type (void)
{
	static GType type = 0;

	if (!type) {
		AtkObjectFactory *factory;

		GTypeInfo info = {
			sizeof (GalA11yETableClass),
			(GBaseInitFunc) NULL,
			(GBaseFinalizeFunc) NULL,
			(GClassInitFunc) et_class_init,
			(GClassFinalizeFunc) NULL,
			NULL,
			sizeof (GalA11yETable),
			0,
			(GInstanceInitFunc) et_init,
			NULL
		};

		static const GInterfaceInfo atk_component_info = {
			(GInterfaceInitFunc) et_atk_component_iface_init,
			(GInterfaceFinalizeFunc) NULL,
			NULL
		};

		factory = atk_registry_get_factory (atk_get_default_registry (), GTK_TYPE_WIDGET);
		parent_type = atk_object_factory_get_accessible_type (factory);

		type = gal_a11y_type_register_static_with_private (
			PARENT_TYPE, "GalA11yETable", &info, 0,
			sizeof (GalA11yETablePrivate), &priv_offset);
		g_type_add_interface_static (type, ATK_TYPE_COMPONENT, &atk_component_info);
	}

	return type;
}
