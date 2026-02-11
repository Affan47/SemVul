check_for_connection (gpointer data)
{
  GdictClientContext *context = data;

#if 0
  g_debug (G_STRLOC ": checking for connection (is connecting:%s)",
           context->priv->is_connecting ? "true" : "false");
#endif

  if (context == NULL)
    return FALSE;

  if (context->priv->is_connecting)
    {
      GError *err = NULL;

      GDICT_NOTE (DICT, "Forcing a disconnection due to timeout");

      g_set_error (&err, GDICT_CLIENT_CONTEXT_ERROR,
                   GDICT_CLIENT_CONTEXT_ERROR_SOCKET,
                   _("Connection timeout for the dictionary server at '%s:%d'"),
                   context->priv->hostname,
                   context->priv->port);

      g_signal_emit_by_name (context, "error", err);

      g_error_free (err);

      gdict_client_context_force_disconnect (context);
    }


  return FALSE;
}
