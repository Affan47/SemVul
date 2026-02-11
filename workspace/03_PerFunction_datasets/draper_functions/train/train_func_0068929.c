cb_colrow_index_counter (gpointer data, gpointer user_data)
{
	ColRowIndex *index = data;
	gint *count = user_data;
	if (data != NULL)
		*count += index->last - index->first + 1;
}
