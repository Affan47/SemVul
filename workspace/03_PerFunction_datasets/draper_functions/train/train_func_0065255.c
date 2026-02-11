visu_data_addTimeout(VisuData *data, guint time,
			   GSourceFunc func, gpointer user_data)
{
  guint *id;

  g_return_val_if_fail(VISU_IS_DATA(data) && func, (guint)0);

  id = g_malloc(sizeof(guint));
  *id = g_timeout_add(time, func, user_data);
  data->priv->timeoutList = g_list_prepend(data->priv->timeoutList, (gpointer)id);
  DBG_fprintf(stderr, "Visu Data: create a new timeout callback : %d.\n", *id);
  return *id;
}
