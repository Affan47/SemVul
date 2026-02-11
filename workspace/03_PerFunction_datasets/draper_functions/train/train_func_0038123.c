debrief_do_keys(int new_k)
{
	switch (new_k) {
		case KEY_TAB:
			debrief_next_tab();
			break;

		case KEY_SHIFTED | KEY_TAB:
			debrief_prev_tab();
			break;

		case KEY_ESC: {
			int pf_flags;
			int choice;


			if (Game_mode & GM_MULTIPLAYER) {
				multi_debrief_esc_hit();
			} else {

				if (!Turned_traitor && !Must_replay_mission && (Game_mode & GM_CAMPAIGN_MODE)) {
					pf_flags = PF_BODY_BIG;
					choice = popup(pf_flags, 3, POPUP_CANCEL, XSTR( "&Yes", 454), XSTR( "&No, retry later", 455), XSTR( "Accept this mission outcome?", 456));
					if (choice == 1) {
						debrief_accept(0);
						gameseq_post_event(GS_EVENT_MAIN_MENU);
					}

					if (choice < 1)
						break;

				} else if ( ( Turned_traitor || Must_replay_mission ) && (Game_mode & GM_CAMPAIGN_MODE)) {

					choice = popup(0, 2, POPUP_NO, POPUP_YES, XSTR( "Because this mission was a failure, you must replay this mission when you continue your campaign.\n\nReturn to the Flight Deck?", 457));
					if (choice <= 0) {
						break;
					}
				}


				gameseq_post_event(GS_EVENT_END_GAME);
			}
		}

		default:
			break;
	}
}
