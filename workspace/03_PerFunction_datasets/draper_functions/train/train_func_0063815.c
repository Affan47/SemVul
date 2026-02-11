tp_properties_context_remove (TpPropertiesContext *ctx, guint property)
{
  g_assert (property < ctx->mixin_cls->num_props);

  tp_intset_remove (ctx->remaining, property);
}
