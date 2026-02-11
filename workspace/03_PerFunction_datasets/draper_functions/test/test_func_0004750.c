gdict_client_context_is_connected (GdictClientContext *context)
{
  g_assert (GDICT_IS_CLIENT_CONTEXT (context));


  if (context->priv->is_connecting)
    return TRUE;

  return (context->priv->channel != NULL && context->priv->source_id != 0);
}
