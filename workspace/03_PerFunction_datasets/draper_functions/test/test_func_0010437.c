tp_properties_mixin_has_property (GObject *obj, const gchar *name,
                                      guint *property)
{
  TpPropertiesMixinClass *mixin_cls = TP_PROPERTIES_MIXIN_CLASS (
                                            G_OBJECT_GET_CLASS (obj));
  guint i;

  for (i = 0; i < mixin_cls->num_props; i++)
    {
      if (!tp_strdiff (mixin_cls->signatures[i].name, name))
        {
          if (property)
            *property = i;

          return TRUE;
        }
    }

  return FALSE;
}
