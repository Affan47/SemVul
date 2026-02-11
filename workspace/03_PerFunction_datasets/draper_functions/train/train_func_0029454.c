grl_magnatune_source_search(GrlSource *source, GrlSourceSearchSpec *ss)
{
  OperationSpec *os = NULL;

  os = g_slice_new0(OperationSpec);
  os->source = ss->source;
  os->operation_id = ss->operation_id;
  os->text = (ss->text == NULL) ? "": ss->text;
  os->count = grl_operation_options_get_count(ss->options);
  os->skip = grl_operation_options_get_skip(ss->options);
  os->callback = ss->callback;
  os->user_data = ss->user_data;
  os->error_code = GRL_CORE_ERROR_SEARCH_FAILED;
  os->magnatune_cb = NULL;

  if (GRL_MAGNATUNE_SOURCE(source)->priv->db == NULL) {

    os->magnatune_cb = magnatune_execute_search;
    magnatune_get_crc_async();
    magnatune_get_db_async(os);
  } else {
    magnatune_execute_search(os);
    magnatune_check_update();
  }
}
