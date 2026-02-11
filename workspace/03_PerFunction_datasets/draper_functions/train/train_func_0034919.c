campaign_room_build_listing()
{
	int font_height = gr_get_font_height();
	int i, y;

	Num_lines = y = 0;

	for (i = 0; i < Num_campaigns; i++) {
		if (Campaign_names[i] != NULL) {

			int flags = 0;
			fs_builtin_mission *fb = game_find_builtin_mission(Campaign_file_names[i]);

			if (fb != NULL) {
				if (fb->flags & FSB_FROM_VOLITION) {
					flags |= READYROOM_FLAG_FROM_VOLITION;
				}
			}

			sim_room_line_add(READYROOM_LINE_CAMPAIGN, Campaign_names[i], Campaign_file_names[i], Cr_list_coords[gr_screen.res][0], y, flags);
			y += font_height + 2;
		}
	}
}
