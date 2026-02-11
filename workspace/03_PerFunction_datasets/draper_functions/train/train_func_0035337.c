equinox_shade_shift (const EquinoxRGB *base, EquinoxRGB *composite, double shade_ratio)
{
	gdouble hue = 0;
	gdouble saturation = 0;
	gdouble brightness = 0;

	g_return_if_fail (base && composite);

	equinox_hsb_from_color (base, &hue, &saturation, &brightness);

	brightness = MIN(brightness*shade_ratio, 1.0);
	brightness = MAX(brightness, 0.0);
	hue += shade_ratio >= 1.0 ? -2.75*shade_ratio : -12*shade_ratio + 12;

	equinox_color_from_hsb (hue, saturation, brightness, composite);
}
