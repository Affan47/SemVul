read_done_cb (GObject *source_object,
              GAsyncResult *res,
              gpointer user_data)
{
  GError *error = NULL;
  GError *wc_error = NULL;
  OperationData *op_data = (OperationData *) user_data;
  gchar *content = NULL;

  if (!grl_net_wc_request_finish (GRL_NET_WC (source_object),
                              res,
                              &content,
                              NULL,
                              &wc_error)) {
    error = g_error_new (GRL_CORE_ERROR,
                         GRL_CORE_ERROR_BROWSE_FAILED,
                         _("Failed to connect: %s"),
                         wc_error->message);
    op_data->bs->callback (op_data->bs->source,
                           op_data->bs->operation_id,
                           NULL,
                           0,
                           op_data->bs->user_data,
                           error);
    g_error_free (wc_error);
    g_error_free (error);
    g_object_unref (op_data->cancellable);
    g_slice_free (OperationData, op_data);

    return;
  }

  xml_parse_result (content, op_data);
}
