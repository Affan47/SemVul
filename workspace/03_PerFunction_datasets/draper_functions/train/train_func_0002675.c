gucharmap_chartable_accessible_get_type (void)
{
  static volatile gsize type__volatile = 0;

  if (g_once_init_enter (&type__volatile))
    {
      GTypeInfo typeinfo =
      {
        0 ,
        (GBaseInitFunc) NULL,
        (GBaseFinalizeFunc) NULL,
        (GClassInitFunc) gucharmap_chartable_accessible_class_init,
        (GClassFinalizeFunc) NULL,
        NULL,
        0 ,
        0,
        (GInstanceInitFunc) gucharmap_chartable_accessible_init,
        NULL
      };
      const GInterfaceInfo atk_table_info =
      {
          (GInterfaceInitFunc) gucharmap_chartable_accessible_table_interface_init,
          (GInterfaceFinalizeFunc) NULL,
          NULL
      };
      const GInterfaceInfo atk_component_info =
      {
          (GInterfaceInitFunc) gucharmap_chartable_accessible_component_interface_init,
          (GInterfaceFinalizeFunc) NULL,
          NULL
      };
      AtkObjectFactory *factory;
      GType derived_type;
      GTypeQuery query;
      GType derived_atk_type;
      GType type;


      derived_type = g_type_parent (GUCHARMAP_TYPE_CHARTABLE);
      factory = atk_registry_get_factory (atk_get_default_registry (),
                                          derived_type);
      derived_atk_type = atk_object_factory_get_accessible_type (factory);
      g_type_query (derived_atk_type, &query);
      typeinfo.class_size = query.class_size;
      typeinfo.instance_size = query.instance_size;

      type = g_type_register_static (derived_atk_type,
                                     "GucharmapChartableAccessible",
                                     &typeinfo, 0);

      g_type_add_interface_static (type, ATK_TYPE_TABLE,
                                   &atk_table_info);
      g_type_add_interface_static (type, ATK_TYPE_COMPONENT,
                                   &atk_component_info);

      g_once_init_leave (&type__volatile, type);
    }

  return type__volatile;
}
