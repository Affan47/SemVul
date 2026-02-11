hud_render_preprocess(float frametime)
{
	Player->subsys_in_view = -1;
	hud_target_clear_display_list();

	if ( (Game_detail_flags & DETAIL_FLAG_HUD) && (supernova_active() >= 3) ) {
		return;
	}

	if ( hud_disabled() ) {
		return;
	}

	if ( Viewer_mode & ( VM_DEAD_VIEW ) ) {
		return;
	}

	if ( Viewer_mode & (VM_EXTERNAL | VM_WARP_CHASE | VM_PADLOCK_ANY ) ) {

		Assert(Player != NULL);
		if ( Player->control_mode != PCM_NORMAL ) {
			return;
		}
	}


	hud_show_message_sender();


	if ( hud_disabled_except_messages() ) {
		return;
	}


	hud_draw_navigation();


	hud_show_selection_set();


	hud_show_asteroid_brackets();


	hud_show_targeting_gauges(frametime);


	hud_process_remote_detonate_missile();


	hud_process_homing_missiles();
}
