collection_window_add(CollectWindow *cw, CollectInfo *ci)
{
	if (!cw) return;

	if (!ci->pixbuf) collection_load_thumb_idle(cw->cd);
	collection_table_file_add(cw->table, ci);
}
