clutter_im_context_real_set_surrounding (ClutterIMContext  *context,
				     const gchar   *text,
				     gint           len,
				     gint           cursor_index)
{
  SurroundingInfo *info = g_object_get_data (G_OBJECT (context),
                                             "clutter-im-surrounding-info");

  if (info)
    {
      g_free (info->text);
      info->text = g_strndup (text, len);
      info->cursor_index = cursor_index;
    }
}
