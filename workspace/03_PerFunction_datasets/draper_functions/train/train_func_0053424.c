tp_base_channel_get_self_handle (TpBaseChannel *chan)
{
  if (TP_HAS_GROUP_MIXIN (chan))
    {
      guint ret = 0;

      tp_group_mixin_get_self_handle (G_OBJECT (chan), &ret, NULL);
      if (ret != 0)
        return ret;
    }

  return tp_base_connection_get_self_handle (chan->priv->conn);
}
