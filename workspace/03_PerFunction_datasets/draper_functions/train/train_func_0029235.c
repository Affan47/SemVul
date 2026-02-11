barracks_display_pilot_stats()
{
	int y = 0;
	int z = Stats_scroll_offset;
	int font_height = gr_get_font_height();
	char *str;
	int i, w, h;
	while (y + font_height <= Barracks_stats_coords[gr_screen.res][BARRACKS_H_COORD]) {
		if (z >= Num_stat_lines) {
			break;
		}

		str = Stat_labels[z];
		if (*str == '*') {
			gr_set_color_fast(&Color_text_heading);
			str++;

			gr_get_string_size(&w, &h, str);
			i = Barracks_stats_coords[gr_screen.res][BARRACKS_Y_COORD] + y + h / 2 - 1;
			gr_line(Barracks_stats_coords[gr_screen.res][BARRACKS_X_COORD], i, Barracks_stats_coords[gr_screen.res][BARRACKS_X_COORD] + Barracks_stats_coords[gr_screen.res][BARRACKS_W_COORD] - w - 2, i);
			gr_line(Barracks_stats_coords[gr_screen.res][BARRACKS_X_COORD] + Barracks_stats_coords[gr_screen.res][BARRACKS_W_COORD] + 1, i, Barracks_stats2_coords[gr_screen.res][BARRACKS_X_COORD] + Barracks_stats2_coords[gr_screen.res][BARRACKS_W_COORD], i);

		} else {
			gr_set_color_fast(&Color_text_normal);
		}

		gr_get_string_size(&w, NULL, str);
		gr_printf(Barracks_stats_coords[gr_screen.res][BARRACKS_X_COORD] + Barracks_stats_coords[gr_screen.res][BARRACKS_W_COORD] - w, Barracks_stats_coords[gr_screen.res][BARRACKS_Y_COORD] + y, "%s", str);
		str = Stats[z];
		if (*str) {
			gr_printf(Barracks_stats2_coords[gr_screen.res][BARRACKS_X_COORD], Barracks_stats_coords[gr_screen.res][BARRACKS_Y_COORD] + y, "%s", str);
		}

		y += font_height;
		z++;
	}
}
