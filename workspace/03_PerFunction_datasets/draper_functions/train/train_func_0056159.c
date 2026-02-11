bt_iter_free_pos(struct bt_iter_pos *iter_pos)
{
	if (!iter_pos)
		return;

	if (iter_pos->type == BT_SEEK_RESTORE && iter_pos->u.restore) {
		if (iter_pos->u.restore->stream_saved_pos) {
			g_array_free(
				iter_pos->u.restore->stream_saved_pos,
				TRUE);
		}
		g_free(iter_pos->u.restore);
	}
	g_free(iter_pos);
}
