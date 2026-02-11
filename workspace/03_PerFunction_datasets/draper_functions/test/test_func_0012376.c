aurora_hsb_from_color (const AuroraRGB *rgb, AuroraHSB *hsb)
{
	gdouble min, max, delta;

	if (rgb->r > rgb->g)
	{
		max = MAX(rgb->r, rgb->b);
		min = MIN(rgb->g, rgb->b);
	}
	else
	{
		max = MAX(rgb->g, rgb->b);
		min = MIN(rgb->r, rgb->b);
	}

	hsb->b = (max + min) / 2.0;

	delta = max -min;

	if (fabs(delta) < 0.0001)
	{
		hsb->h = 0;
		hsb->s = 0;
	}
	else
	{
		if (hsb->b <= 0.5)
			hsb->s = (max - min) / (max + min);
		else
			hsb->s = (max - min) / (2.0 - max - min);

		if (rgb->r == max)
			hsb->h = (rgb->g - rgb->b) / delta;
		else if (rgb->g == max)
			hsb->h = 2.0 + (rgb->b - rgb->r) / delta;
		else if (rgb->b == max)
			hsb->h = 4.0 + (rgb->r - rgb->g) / delta;

		hsb->h /= 6.0;
		if (hsb->h < 0.0)
			hsb->h += 1.0;
	}
}
