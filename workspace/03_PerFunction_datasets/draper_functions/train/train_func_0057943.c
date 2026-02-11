goo_canvas_accessible_get_type (void)
{
  static GType g_define_type_id = 0;

  if (G_UNLIKELY (g_define_type_id == 0))
    {
      AtkObjectFactory *factory;
      GType parent_atk_type;
      GTypeQuery query;
      GTypeInfo tinfo = { 0 };


      factory = atk_registry_get_factory (atk_get_default_registry (),
					  GTK_TYPE_WIDGET);
      if (!factory)
	return G_TYPE_INVALID;

      parent_atk_type = atk_object_factory_get_accessible_type (factory);
      if (!parent_atk_type)
	return G_TYPE_INVALID;

      g_type_query (parent_atk_type, &query);
      tinfo.class_init = (GClassInitFunc) goo_canvas_accessible_class_init;
      tinfo.class_size = query.class_size;
      tinfo.instance_size = query.instance_size;
      g_define_type_id = g_type_register_static (parent_atk_type,
						 "GooCanvasAccessible",
						 &tinfo, 0);
    }

  return g_define_type_id;
}
