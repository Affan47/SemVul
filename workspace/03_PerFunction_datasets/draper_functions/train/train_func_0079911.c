nemo_list_view_get_item_count (NemoView *view)
{
	g_return_val_if_fail (NEMO_IS_LIST_VIEW (view), 0);

	return nemo_list_model_get_length (NEMO_LIST_VIEW (view)->details->model);
}
