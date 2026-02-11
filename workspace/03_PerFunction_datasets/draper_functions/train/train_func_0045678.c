brief_exit_loop_pressed()
{
	int val = popup(PF_USE_NEGATIVE_ICON | PF_USE_AFFIRMATIVE_ICON, 2, POPUP_NO, POPUP_YES, XSTR( "Exit Loop\n\n\n\nAre you sure you want to leave the mission loop?", 1489));


	if (val <= 0) {
		return;
	}


	mission_campaign_exit_loop();
}
