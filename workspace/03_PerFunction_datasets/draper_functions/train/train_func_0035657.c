for_each_child_done_cb (gpointer user_data)
{
	ForEachChildData *fec = user_data;

	g_source_remove (fec->source_id);
	_g_info_data_freev (&(fec->current));
	if (fec->done_func)
		fec->done_func (fec->error, fec->user_data);
	for_each_child_data_free (fec);

	return FALSE;
}
