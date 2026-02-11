send_movie_info (OperationData *op_data)
{
  GrlMedia *media;
  gboolean last = FALSE;

  if (g_cancellable_is_cancelled (op_data->cancellable)) {
    op_data->bs->callback (op_data->bs->source,
                           op_data->bs->operation_id,
                           NULL,
                           0,
                           op_data->bs->user_data,
                           NULL);
    last = TRUE;
  } else {
    GrlAppleTrailersSource *source =
      GRL_APPLE_TRAILERS_SOURCE (op_data->bs->source);
    gint count = grl_operation_options_get_count (op_data->bs->options);

    media = build_media_from_movie (op_data->xml_entries,
                                    source->priv->large_poster);
    last =
      !op_data->xml_entries->next || count == 1;

    op_data->bs->callback (op_data->bs->source,
                           op_data->bs->operation_id,
                           media,
                           last? 0: -1,
                           op_data->bs->user_data,
                           NULL);
    op_data->xml_entries = op_data->xml_entries->next;
    if (!last)
      grl_operation_options_set_count (op_data->bs->options, count - 1);
  }

  if (last) {
    xmlFreeDoc (op_data->xml_doc);
    g_object_unref (op_data->cancellable);
    g_slice_free (OperationData, op_data);
  }

  return !last;
}
