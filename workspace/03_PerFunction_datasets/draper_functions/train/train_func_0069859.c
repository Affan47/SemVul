gbf_tree_data_new_shortcut (GbfTreeData *src)
{
	GbfTreeData *data = g_slice_new0 (GbfTreeData);

	data->type = GBF_TREE_NODE_SHORTCUT;
	data->node = src->node;
	data->name = g_strdup (src->name);
	data->group = src->group == NULL ? NULL : g_object_ref (src->group);
	data->target = g_strdup (src->target);
	data->source = src->source == NULL ? NULL : g_object_ref (src->source);
	data->is_shortcut = TRUE;
	data->shortcut = src;


	return data;
}
