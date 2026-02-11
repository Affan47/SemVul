atk_object_factory_get_type (void)
{
  static GType type = 0;

  if (!type) {
    GTypeInfo tinfo =
    {
      sizeof (AtkObjectFactoryClass),
      (GBaseInitFunc) NULL,
      (GBaseFinalizeFunc) NULL,
      (GClassInitFunc) atk_object_factory_class_init,
      (GClassFinalizeFunc) NULL,
      NULL,
      sizeof (AtkObjectFactory),
      0,
      (GInstanceInitFunc) NULL,
      NULL
    };

    type = g_type_register_static (G_TYPE_OBJECT, "AtkObjectFactory", &tinfo, 0);
  }
  return type;
}
