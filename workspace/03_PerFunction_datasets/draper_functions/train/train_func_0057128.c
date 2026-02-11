gnome_rr_labeler_hide (GnomeRRLabeler *labeler)
{
	int i;

	g_return_if_fail (GNOME_IS_RR_LABELER (labeler));

	if (labeler->windows == NULL)
		return;

	for (i = 0; i < labeler->num_outputs; i++)
		if (labeler->windows[i] != NULL) {
			gtk_widget_destroy (labeler->windows[i]);
			labeler->windows[i] = NULL;
		}
	g_free (labeler->windows);
	labeler->windows = NULL;
}
