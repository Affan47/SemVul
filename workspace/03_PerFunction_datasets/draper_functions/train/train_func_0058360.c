index_compare (gconstpointer a, gconstpointer b, gpointer userdata)
{
	guint la = ( (Region *)a)->line;
	guint lb = ( (Region *)b)->line;

	return la < lb ? -1 : (la > lb ? 1 : 0);
}
