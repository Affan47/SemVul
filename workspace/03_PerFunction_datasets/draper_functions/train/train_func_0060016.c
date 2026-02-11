gtv_wire_plugins_audio (gtk_video_private_t *priv,
				    xine_audio_port_t *audio_port)
{

  GList *list = priv->post_audio.enable
		? g_list_copy (priv->post_audio.list) : NULL;
  GList *item, *next = NULL;

  if (priv->vis_active && priv->vis_plugin)
    list = g_list_prepend (list, priv->vis_plugin);

  item = g_list_last (list);
  while (item)
  {
    xine_post_out_t *out = gtv_post_output_audio (item->data);
    if (next)
      xine_post_wire (out, gtv_post_input_audio (next->data));
    else
      xine_post_wire_audio_port (out, audio_port);
    next = item;
    item = g_list_previous (item);
  }

  if (next)
    xine_post_wire (xine_get_audio_source (priv->stream),
		    gtv_post_input_audio (next->data));

  g_list_free (list);
}
