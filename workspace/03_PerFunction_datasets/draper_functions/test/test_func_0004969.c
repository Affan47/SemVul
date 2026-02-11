tp_proxy_pending_call_v0_take_pending_call (TpProxyPendingCall *pc,
                                            DBusGProxyCall *pending_call)
{
  g_return_if_fail (pc->priv == pending_call_magic);
  g_return_if_fail (pc->pending_call == NULL);
  g_return_if_fail (pc->proxy != NULL);

  pc->pending_call = pending_call;
}
