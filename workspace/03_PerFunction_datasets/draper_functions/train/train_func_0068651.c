gnome_rr_labeler_new (GnomeRRConfig *config)
{
	GnomeRRLabeler *labeler;

	g_return_val_if_fail (config != NULL, NULL);

	labeler = g_object_new (GNOME_TYPE_RR_LABELER, NULL);
	labeler->config = config;

	setup_from_config (labeler);

	return labeler;
}
