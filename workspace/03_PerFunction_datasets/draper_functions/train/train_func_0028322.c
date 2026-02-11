gucharmap_charmap_set_chapters_model (GucharmapCharmap  *charmap,
                                      GucharmapChaptersModel *model)
{
  GucharmapCharmapPrivate *priv = charmap->priv;
  GObject *object = G_OBJECT (charmap);
  gunichar wc;

  g_object_freeze_notify (object);

  g_object_notify (G_OBJECT (charmap), "chapters-model");

  gucharmap_chapters_view_set_model (priv->chapters_view, model);
  if (!model) {
    g_object_thaw_notify (object);
    return;
  }

  if (priv->last_character_set) {
    wc = gucharmap_chartable_get_active_character (priv->chartable);
    gucharmap_charmap_set_active_character (charmap, wc);
  }

  priv->last_character_set = TRUE;

  g_object_thaw_notify (object);
}
