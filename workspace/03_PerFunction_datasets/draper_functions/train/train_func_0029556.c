clutter_text_set_font_description_internal (ClutterText          *self,
                                            PangoFontDescription *desc,
                                            gboolean              is_default_font)
{
  ClutterTextPrivate *priv = self->priv;

  priv->is_default_font = is_default_font;

  if (priv->font_desc == desc ||
      pango_font_description_equal (priv->font_desc, desc))
    return;

  if (priv->font_desc != NULL)
    pango_font_description_free (priv->font_desc);

  priv->font_desc = pango_font_description_copy (desc);


  g_free (priv->font_name);
  priv->font_name = pango_font_description_to_string (priv->font_desc);

  clutter_text_dirty_cache (self);

  if (clutter_text_buffer_get_length (get_buffer (self)) != 0)
    clutter_actor_queue_relayout (CLUTTER_ACTOR (self));

  g_object_notify_by_pspec (G_OBJECT (self), obj_props[PROP_FONT_DESCRIPTION]);
}
