inf_adopted_request_log_remove_requests(InfAdoptedRequestLog* log,
                                        guint up_to)
{
  InfAdoptedRequestLogPrivate* priv;
  guint i;

  g_return_if_fail(INF_ADOPTED_IS_REQUEST_LOG(log));

  priv = INF_ADOPTED_REQUEST_LOG_PRIVATE(log);

  g_return_if_fail(up_to >= priv->begin && up_to <= priv->end);

  g_return_if_fail(
    up_to == priv->begin ||
    priv->entries[priv->offset + up_to - priv->begin - 1].upper_related ==
    &priv->entries[priv->offset + up_to - priv->begin - 1]
  );

  for(i = priv->offset; i < priv->offset + (up_to - priv->begin); ++i)
    g_object_unref(G_OBJECT(priv->entries[i].request));

  g_object_freeze_notify(G_OBJECT(log));


  if(priv->next_undo != NULL)
  {
    if(priv->next_undo < priv->entries + priv->offset + (up_to - priv->begin))
    {
      priv->next_undo = NULL;
      g_object_notify(G_OBJECT(log), "next-undo");
    }
  }

  if(priv->next_redo != NULL)
  {
    if(priv->next_redo < priv->entries + priv->offset + (up_to - priv->begin))
    {
      priv->next_redo = NULL;
      g_object_notify(G_OBJECT(log), "next-redo");
    }
  }

  priv->offset += (up_to - priv->begin);
  priv->begin = up_to;

  g_object_notify(G_OBJECT(log), "begin");
  inf_adopted_request_log_verify_related(log);
  g_object_thaw_notify(G_OBJECT(log));
}
