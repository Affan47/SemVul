get_result_data(GtkTreeModel *model, GtkTreeIter *iter)
{
	static const GValue zero_value;
	GValue value = zero_value;
	struct result_data *rd;

	gtk_tree_model_get_value(model, iter, 0, &value);
	rd = g_value_get_pointer(&value);
	record_check(rd->record);
	g_assert(rd->record->refcount > 0);
	return rd;
}
