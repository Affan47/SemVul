is_gail_loaded (GType derived_type)
{
  AtkObjectFactory *factory;
  GType derived_atk_type;

  factory = atk_registry_get_factory (atk_get_default_registry(),
				      derived_type);

  derived_atk_type = atk_object_factory_get_accessible_type (factory);
  if (g_type_is_a (derived_atk_type, GTK_TYPE_ACCESSIBLE))
    return TRUE;

  return FALSE;
}
