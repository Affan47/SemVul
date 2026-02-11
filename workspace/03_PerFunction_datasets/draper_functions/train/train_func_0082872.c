visu_data_restore(VisuData *data)
{
  float zeros[3] = {0.f, 0.f, 0.f};

  g_return_val_if_fail(VISU_IS_DATA(data), FALSE);

  visu_box_setExtension(data->priv->box, zeros);
  return visu_node_array_removeAllDuplicateNodes(VISU_NODE_ARRAY(data));
}
