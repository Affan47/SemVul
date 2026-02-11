gegl_node_remove_context (GeglNode *self,
                          gpointer  context_id)
{
  GeglOperationContext *context;

  g_return_if_fail (GEGL_IS_NODE (self));
  g_return_if_fail (context_id != NULL);

  context = gegl_node_get_context (self, context_id);
  g_mutex_lock (self->mutex);
  if (!context)
    {
      g_warning ("didn't find context %p for %s",
                 context_id, gegl_node_get_debug_name (self));
      g_mutex_unlock (self->mutex);
      return;
    }
  g_hash_table_remove (self->priv->contexts, context_id);
  gegl_operation_context_destroy (context);
  g_mutex_unlock (self->mutex);
}
