prepare_async_result (DeepCountState *state)
{
  ShellMimeSniffer *self = state->self;
  GArray *results;
  GPtrArray *sniffed_mime;
  SniffedResult result;

  sniffed_mime = g_ptr_array_new ();
  results = g_array_new (TRUE, TRUE, sizeof (SniffedResult));

  if (state->total_items == 0)
    goto out;

  result.type = "x-content/video";
  result.ratio = (gdouble) state->video_count / (gdouble) state->total_items;
  g_array_append_val (results, result);

  result.type = "x-content/audio";
  result.ratio = (gdouble) state->audio_count / (gdouble) state->total_items;
  g_array_append_val (results, result);

  result.type = "x-content/pictures";
  result.ratio = (gdouble) state->image_count / (gdouble) state->total_items;
  g_array_append_val (results, result);

  result.type = "x-content/documents";
  result.ratio = (gdouble) state->document_count / (gdouble) state->total_items;
  g_array_append_val (results, result);

  g_array_sort (results, results_cmp_func);

  result = g_array_index (results, SniffedResult, 0);
  g_ptr_array_add (sniffed_mime, g_strdup (result.type));


  result = g_array_index (results, SniffedResult, 1);
  if (result.ratio < HIGH_SCORE_RATIO)
    goto out;
  g_ptr_array_add (sniffed_mime, g_strdup (result.type));

  result = g_array_index (results, SniffedResult, 2);
  if (result.ratio < HIGH_SCORE_RATIO)
    goto out;
  g_ptr_array_add (sniffed_mime, g_strdup (result.type));

 out:
  g_ptr_array_add (sniffed_mime, NULL);
  self->priv->sniffed_mime = (gchar **) g_ptr_array_free (sniffed_mime, FALSE);

  g_array_free (results, TRUE);
  g_simple_async_result_complete_in_idle (self->priv->async_result);
}
