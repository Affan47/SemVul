sim_room_button_pressed(int n)
{
	switch (n) {
		case SCROLL_UP_BUTTON:
			sim_room_scroll_screen_up();
			Sim_room_slider.forceUp();
			break;

		case SCROLL_DOWN_BUTTON:
			sim_room_scroll_screen_down();
			Sim_room_slider.forceDown();
			break;

		case MISSION_TAB:
			Simroom_show_all = 0;
			Player->readyroom_listing_mode = MODE_MISSIONS;
			Selected_line = Scroll_offset = 0;
			gamesnd_play_iface(SND_USER_SELECT);
			sim_room_build_listing();
			break;

		case CAMPAIGN_TAB:
			if ( !strlen(Campaign.filename) ) {
				popup( PF_NO_NETWORKING, 1, POPUP_OK, XSTR( "The currently active campaign cannot be found, unable to switch to campaign mode!", 1612));
				break;
			}

			if (Player->readyroom_listing_mode != MODE_CAMPAIGNS)
				Simroom_show_all = 0;

			Player->readyroom_listing_mode = MODE_CAMPAIGNS;
			Scroll_offset = 0;
			gamesnd_play_iface(SND_USER_SELECT);
			sim_room_build_listing();
			break;

		case COMMIT_BUTTON:
			sim_room_commit();
			break;

		case HELP_BUTTON:
			launch_context_help();
			gamesnd_play_iface(SND_HELP_PRESSED);
			break;

		case OPTIONS_BUTTON:
			gamesnd_play_iface(SND_SWITCH_SCREENS);
			gameseq_post_event(GS_EVENT_OPTIONS_MENU);
			return 1;

		case TECH_DATABASE_BUTTON:
			gamesnd_play_iface(SND_SWITCH_SCREENS);
			gameseq_post_event(GS_EVENT_TECH_MENU);
			return 1;

		case CUTSCENES_BUTTON:
			gamesnd_play_iface(SND_SWITCH_SCREENS);
			gameseq_post_event(GS_EVENT_GOTO_VIEW_CUTSCENES_SCREEN);
			return 1;

		case CREDITS_BUTTON:
			gamesnd_play_iface(SND_SWITCH_SCREENS);
			gameseq_post_event(GS_EVENT_CREDITS);
			return 1;
	}

	return 0;
}
