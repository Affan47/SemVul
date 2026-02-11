murrine_invert_text (const MurrineRGB *a, MurrineRGB *b)
{
	double red;
	double green;
	double blue;

	red   = a->r;
	green = a->g;
	blue  = a->b;

	murrine_rgb_to_hls (&red, &green, &blue);

	if (green < 0.8)
		green = 1.0;
	else
		green = 0.0;

	murrine_hls_to_rgb (&red, &green, &blue);

	b->r = red;
	b->g = green;
	b->b = blue;
}
