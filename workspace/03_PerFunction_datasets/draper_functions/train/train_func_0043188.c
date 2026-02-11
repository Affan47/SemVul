gnuplot_png_set_default_scale (double s)
{
    if (s >= 0.5 && s <= 2.0) {
	default_png_scale = s;
    }
}
