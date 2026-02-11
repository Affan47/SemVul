lx_sync_to_obs(gpointer dialog)
{
	struct obs_data *obs;
	struct tele_t *tele;
	int ret;
	GtkWidget *main_window = g_object_get_data(G_OBJECT (dialog), "image_window");

	obs = gtk_object_get_data(GTK_OBJECT(dialog), "obs_data");
	if (obs == NULL) {
		err_printf("No obs data for syncing\n");
		return -1;
	}
	tele = tele_find(main_window);
	if (! tele)
		return -1;
	ret = tele_set_coords(tele, TELE_COORDS_SYNC, obs->ra, obs->dec, obs->equinox);
	return ret;
}
