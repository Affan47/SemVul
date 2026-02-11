sw_cacheable_is_ready (SwCacheable *self)
{
  SwCacheableInterface *iface = SW_CACHEABLE_GET_IFACE (self);
  g_return_val_if_fail (iface, FALSE);

  return iface->is_ready (self);
}
