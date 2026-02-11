read_url_async (GrlAppleTrailersSource *source,
                const gchar *url,
                OperationData *op_data)
{
  if (!source->priv->wc)
    source->priv->wc = grl_net_wc_new ();

  GRL_DEBUG ("Opening '%s'", url);
  grl_net_wc_request_async (source->priv->wc,
                        url,
                        op_data->cancellable,
                        read_done_cb,
                        op_data);
}
