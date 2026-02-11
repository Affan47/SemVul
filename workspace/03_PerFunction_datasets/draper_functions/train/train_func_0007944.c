model_node_inserted (GeditFileBrowserStore *model,
		     FileBrowserNode        *node)
{
	return node == model->priv->virtual_root ||
	       (model_node_visibility (model, node) && node->inserted);
}
