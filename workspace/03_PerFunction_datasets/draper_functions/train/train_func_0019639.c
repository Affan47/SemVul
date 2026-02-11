filter_sort_ext_len_cb(gconstpointer a, gconstpointer b)
{
	gchar *sa = (gchar *)a;
	gchar *sb = (gchar *)b;

	gint len_a = strlen(sa);
	gint len_b = strlen(sb);

	if (len_a > len_b) return -1;
	if (len_a < len_b) return 1;
	return 0;
}
