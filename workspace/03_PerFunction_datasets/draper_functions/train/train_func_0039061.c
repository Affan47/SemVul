glade_widget_copy_packing_props (GladeWidget * parent,
                                 GladeWidget * child,
                                 GladeWidget * template_widget)
{
  GladeProperty *dup_prop, *orig_prop;
  GList *l;

  g_return_if_fail (child->priv->parent == parent);

  glade_widget_set_packing_properties (child, parent);

  for (l = child->priv->packing_properties; l && l->data; l = l->next)
    {
      GladePropertyClass *pclass;

      dup_prop  = GLADE_PROPERTY (l->data);
      pclass    = glade_property_get_class (dup_prop);
      orig_prop = glade_widget_get_pack_property (template_widget, glade_property_class_id (pclass));

      glade_property_set_value (dup_prop, glade_property_inline_value (orig_prop));
    }
}
