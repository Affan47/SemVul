visu_data_dispose(GObject* obj)
{
  VisuData *data;

  DBG_fprintf(stderr, "Visu Data: dispose object %p.\n", (gpointer)obj);

  data = VISU_DATA(obj);
  if (data->priv->dispose_has_run)
    return;
  data->priv->dispose_has_run = TRUE;

#if DEBUG == 1
  g_mem_profile();
#endif

  DBG_fprintf(stderr, "Visu Data: emit a 'objectFreed' signal.\n");
  g_signal_emit(obj, visu_data_signals[VISU_DATA_FREED_SIGNAL],
		0, NULL);

  visu_data_setBox(VISU_BOXED(data), (VisuBox*)0, FALSE);

  visu_data_node_setUsed(dataNodeCoord, data, 0);


  G_OBJECT_CLASS(visu_data_parent_class)->dispose(obj);
}
