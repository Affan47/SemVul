mono_seq_point_data_get_il_offset (char *path, guint32 method_token, guint32 method_index, guint32 native_offset, guint32 *il_offset)
{
	SeqPointData sp_data;
	MonoSeqPointInfo *seq_points;
	SeqPoint sp;

	if (!mono_seq_point_data_read (&sp_data, path))
		return FALSE;

	if (!mono_seq_point_data_get (&sp_data, method_token, method_index, &seq_points))
		return FALSE;

	if (!mono_seq_point_find_prev_by_native_offset (seq_points, native_offset, &sp))
		return FALSE;

	*il_offset = sp.il_offset;

	return TRUE;
}
