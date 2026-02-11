free_pdata (gpointer data, gpointer user_data)
{
	PData *d = (PData *) data;

	if (d->str)
		g_free (d->str);
	g_free (d);
}
