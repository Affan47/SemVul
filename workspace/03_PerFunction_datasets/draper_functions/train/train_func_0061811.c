mx_droppable_is_enabled (MxDroppable *droppable)
{
  gboolean retval = FALSE;

  g_return_val_if_fail (MX_IS_DROPPABLE (droppable), FALSE);

  g_object_get (G_OBJECT (droppable), "drop-enabled", &retval, NULL);

  return retval;
}
