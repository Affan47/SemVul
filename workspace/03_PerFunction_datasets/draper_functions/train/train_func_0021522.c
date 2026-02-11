make_palette (GnomeRRLabeler *labeler)
{


	double start_hue;
	double end_hue;
	int i;

	g_assert (labeler->num_outputs > 0);

	labeler->palette = g_new (GdkColor, labeler->num_outputs);

	start_hue = 0.0;
	end_hue   = 2.0/3;

	for (i = 0; i < labeler->num_outputs; i++) {
		double h, s, v;
		double r, g, b;

		h = start_hue + (end_hue - start_hue) / labeler->num_outputs * i;
		s = 1.0 / 3;
		v = 1.0;

		gtk_hsv_to_rgb (h, s, v, &r, &g, &b);

		labeler->palette[i].red   = (int) (65535 * r + 0.5);
		labeler->palette[i].green = (int) (65535 * g + 0.5);
		labeler->palette[i].blue  = (int) (65535 * b + 0.5);
	}
}
