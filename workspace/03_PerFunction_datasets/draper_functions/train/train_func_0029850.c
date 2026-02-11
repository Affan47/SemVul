mono_seq_point_find_prev_by_native_offset (MonoSeqPointInfo* info, int native_offset, SeqPoint* seq_point)
{
	SeqPoint prev_seq_point;
	gboolean  is_first = TRUE;
	SeqPointIterator it;
	mono_seq_point_iterator_init (&it, info);
	while (mono_seq_point_iterator_next (&it) && it.seq_point.native_offset <= native_offset) {
		memcpy (&prev_seq_point, &it.seq_point, sizeof (SeqPoint));
		is_first = FALSE;
	}

	if (!is_first && prev_seq_point.native_offset <= native_offset) {
		memcpy (seq_point, &prev_seq_point, sizeof (SeqPoint));
		return TRUE;
	}

	return FALSE;
}
