render(float frametime)
{
	int			target_objnum, sx, sy;
	object		*targetp;
	vertex lock_point;

	if (Player_ai->target_objnum == -1) {
		return;
	}

	if (Player->target_is_dying) {
		return;
	}

	if (!Players[Player_num].lock_indicator_visible){
		return;
	}

	target_objnum = Player_ai->target_objnum;
	Assert(target_objnum != -1);
	targetp = &Objects[target_objnum];


	if ( !ship_secondary_bank_has_ammo(Player_obj->instance) ) {
		return;
	}

	bool in_frame = g3_in_frame() > 0;
	if(!in_frame)
		g3_start_frame(0);
	gr_set_screen_scale(base_w, base_h);


	g3_rotate_vertex(&lock_point, &lock_world_pos);
	g3_project_vertex(&lock_point);
	if (lock_point.codes & PF_OVERFLOW) {
		gr_reset_screen_scale();

		if(!in_frame)
			g3_end_frame();

		return;
	}

	hud_set_iff_color(targetp);


	if (Player_ai->current_target_is_locked) {
		sx = fl2i(lock_point.screen.xyw.x);
		sy = fl2i(lock_point.screen.xyw.y);
		gr_unsize_screen_pos(&sx, &sy);


		renderLockTriangles(sx, sy, frametime);
	} else {
		sx = fl2i(lock_point.screen.xyw.x) - (Player->current_target_sx - Players[Player_num].lock_indicator_x);
		sy = fl2i(lock_point.screen.xyw.y) - (Player->current_target_sy - Players[Player_num].lock_indicator_y);
		gr_unsize_screen_pos(&sx, &sy);
	}


	Lock_gauge.sx = sx - Lock_gauge_half_w;
	Lock_gauge.sy = sy - Lock_gauge_half_h;
	if(Player_ai->current_target_is_locked){
		Lock_gauge.time_elapsed = 0.0f;
		hud_anim_render(&Lock_gauge, 0.0f, 1);
	} else {
		hud_anim_render(&Lock_gauge, frametime, 1);
	}

	gr_reset_screen_scale();
	if(!in_frame)
		g3_end_frame();
}
