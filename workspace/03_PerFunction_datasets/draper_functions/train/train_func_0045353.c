_on_web_view_load_error (WebKitWebView  *webview,
                         WebKitWebFrame *frame,
                         const char     *uri,
                         GError         *error,
                         PhotoData      *data)
{

  if (error->domain == WEBKIT_NETWORK_ERROR &&
      error->code == WEBKIT_NETWORK_ERROR_CANCELLED)
    return TRUE;

  data->error = TRUE;

  g_printerr (_("Error while loading '%s': %s\n"), uri, error->message);

  gtk_main_quit ();

  return TRUE;
}
