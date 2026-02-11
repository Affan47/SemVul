clear_cache(GtkWidget *widget,gpointer *data)
{

	LOG(LOG_DEBUG, "IN : clear_cache()");

	remove_recursive(cache_dir);

	LOG(LOG_DEBUG, "OUT : clear_cache()");
	return(TRUE);
}
