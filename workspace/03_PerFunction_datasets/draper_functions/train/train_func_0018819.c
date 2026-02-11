clutter_text_set_use_markup_internal (ClutterText *self,
                                      gboolean     use_markup)
{
  ClutterTextPrivate *priv = self->priv;

  if (priv->use_markup != use_markup)
    {
      priv->use_markup = use_markup;


      if (priv->effective_attrs != NULL)
        {
          pango_attr_list_unref (priv->effective_attrs);
          priv->effective_attrs = NULL;
        }

      if (priv->markup_attrs)
        {
          pango_attr_list_unref (priv->markup_attrs);
          priv->markup_attrs = NULL;
        }

      g_object_notify_by_pspec (G_OBJECT (self), obj_props[PROP_USE_MARKUP]);
    }
}
