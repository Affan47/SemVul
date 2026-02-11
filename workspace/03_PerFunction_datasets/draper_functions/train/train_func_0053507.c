recompute_adjusted_palette(int brightness_or_gamma_changed)
{
	int i;


	if (brightness_or_gamma_changed)
		for (i = 0; i < sizeof(color_correct_table); i++)
		{
			int value = (int)(255.0 * (global_brightness * global_brightness_adjust) * pow((double)i * (1.0 / 255.0), 1.0 / global_gamma) + 0.5);
			color_correct_table[i] = (value < 0) ? 0 : (value > 255) ? 255 : value;
		}


	for (i = 0; i < Machine->drv->total_colors; i++)
		internal_modify_pen(i, game_palette[i], pen_brightness[i]);
}
