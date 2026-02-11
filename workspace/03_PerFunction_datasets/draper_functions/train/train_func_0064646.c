release_operation_data (guint operation_id)
{
  GCancellable *cancellable = grl_operation_get_data (operation_id);

  g_clear_object (&cancellable);
}
