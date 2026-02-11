clutter_text_set_use_markup (ClutterText *self,
			     gboolean     setting)
{
  const gchar *text;

  g_return_if_fail (CLUTTER_IS_TEXT (self));

  text = clutter_text_buffer_get_text (get_buffer (self));

  clutter_text_set_use_markup_internal (self, setting);

  if (setting)
    clutter_text_set_markup_internal (self, text);

  clutter_text_dirty_cache (self);

  clutter_actor_queue_relayout (CLUTTER_ACTOR (self));
}
