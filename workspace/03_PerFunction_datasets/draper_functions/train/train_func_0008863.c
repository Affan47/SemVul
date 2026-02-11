mono_seq_point_data_get (SeqPointData *data, guint32 method_token, guint32 method_index, MonoSeqPointInfo** info)
{
	int i;

	for (i=0; i<data->entry_count; i++) {
		if (data->entries [i].method_token == method_token && (method_index == 0xffffff || data->entries [i].method_index == method_index)) {
			(*info) = data->entries [i].seq_points;
			return TRUE;
		}
	}
	return FALSE;
}
