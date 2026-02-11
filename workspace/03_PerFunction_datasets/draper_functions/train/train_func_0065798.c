brief_render_map(int stage_num, float frametime)
{
	gr_set_clip(bscreen.map_x1 + 1, bscreen.map_y1 + 1, bscreen.map_x2 - bscreen.map_x1 - 1, bscreen.map_y2 - bscreen.map_y1 - 2);

    if (stage_num >= Briefing->num_stages) {
		gr_reset_clip();
		return;
	}

	Assert(Briefing);

	g3_start_frame(0);
	g3_set_view_matrix(&Current_cam_pos, &Current_cam_orient, 0.5f);

	brief_maybe_create_new_grid(The_grid, &Current_cam_pos, &Current_cam_orient);
	brief_render_grid(The_grid);

	brief_render_fade_outs(frametime);


	brief_render_icons(stage_num, frametime);

	if ( Cam_target_reached && brief_text_wipe_finished() ) {
		if ( Play_highlight_flag ) {
			brief_start_highlight_anims(stage_num);
			Play_highlight_flag = 0;
		}
	}

	anim_render_all(ON_BRIEFING_SELECT, frametime);

	gr_reset_clip();
	g3_end_frame();
}
