mono_seq_point_data_add (SeqPointData *data, guint32 method_token, guint32 method_index, MonoSeqPointInfo* info)
{
	int i;

	g_assert (data->entry_count < data->entry_capacity);
	i = data->entry_count++;
	data->entries [i].seq_points = info;
	data->entries [i].method_token = method_token;
	data->entries [i].method_index = method_index;
	data->entries [i].free_seq_points = FALSE;
}
