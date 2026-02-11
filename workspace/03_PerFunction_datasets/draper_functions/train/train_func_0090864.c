prepare_depends (TpProxy *self,
    GQuark name)
{
  const TpProxyFeature *feature;

  feature = tp_proxy_subclass_get_feature (G_OBJECT_TYPE (self), name);
  g_assert (feature->depends_on != NULL);

  tp_proxy_prepare_async (self, feature->depends_on, depends_prepare_cb, NULL);
}
