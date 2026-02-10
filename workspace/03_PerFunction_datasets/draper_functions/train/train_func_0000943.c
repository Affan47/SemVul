read_url_async (const gchar *url,
                GCancellable *cancellable,
                AsyncReadCbFunc callback,
                gpointer user_data)
{
  AsyncReadCb *arc;
  GrlNetWc *wc;

  wc = get_wc ();
  if (!wc)
    return;

  arc = g_slice_new0 (AsyncReadCb);
  arc->url = g_strdup (url);
  arc->callback = callback;
  arc->user_data = user_data;

  GRL_DEBUG ("Opening async '%s'", url);
  grl_net_wc_request_async (wc,
                        url,
                        cancellable,
                        read_done_cb,
                        arc);
}
