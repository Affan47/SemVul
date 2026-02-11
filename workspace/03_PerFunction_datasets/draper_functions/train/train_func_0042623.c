tp_automatic_proxy_factory_dup (void)
{
  static TpAutomaticProxyFactory *singleton = NULL;

  if (singleton != NULL)
    return g_object_ref (singleton);

  singleton = _tp_automatic_proxy_factory_new ();

  g_object_add_weak_pointer (G_OBJECT (singleton), (gpointer) &singleton);

  return singleton;
}
