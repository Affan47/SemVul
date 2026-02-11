has_similar_mode (GnomeRROutput *output, GnomeRRMode *mode)
{
    int i;
    GnomeRRMode **modes = gnome_rr_output_list_modes (output);
    int width = gnome_rr_mode_get_width (mode);
    int height = gnome_rr_mode_get_height (mode);

    for (i = 0; modes[i] != NULL; ++i)
    {
	GnomeRRMode *m = modes[i];

	if (gnome_rr_mode_get_width (m) == width	&&
	    gnome_rr_mode_get_height (m) == height)
	{
	    return TRUE;
	}
    }

    return FALSE;
}
