tracker_evt_preupdate_sources_cb (GObject              *object,
                                  GAsyncResult         *result,
                                  tracker_evt_update_t *evt)
{
  GError *error = NULL;

  GRL_DEBUG ("%s: evt=%p", __FUNCTION__, evt);

  evt->cursor = tracker_sparql_connection_query_finish (grl_tracker_connection,
                                                        result, &error);

  if (error != NULL) {
    GRL_WARNING ("\tCannot handle datasource request : %s", error->message);

    g_error_free (error);

    tracker_evt_update_items (evt);
    tracker_evt_update_orphans (evt);
    return;
  }

  tracker_sparql_cursor_next_async (evt->cursor, NULL,
                                    (GAsyncReadyCallback) tracker_evt_preupdate_sources_item_cb,
                                    (gpointer) evt);
}
