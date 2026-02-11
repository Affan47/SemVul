mission_load_menu_init()
{
	int i;
	char wild_card[256];
	Assert( mlm_active == 0 );
	mlm_active = 1;

	memset(wild_card, 0, 256);
	strcpy_s(wild_card, NOX("*"));
	strcat_s(wild_card, FS_MISSION_FILE_EXT);
	mlm_nfiles = cf_get_file_list( MLM_MAX_MISSIONS, mlm_missions, CF_TYPE_MISSIONS, wild_card, CF_SORT_NAME );
	jtmp_nfiles = 0;

	Assert(mlm_nfiles <= MLM_MAX_MISSIONS);

	mlm_window.create( 100,100,500,300, 0 );

	mlm_ok.create( &mlm_window, NOX("Ok"), 125, 420, 80, 40 );
	mlm_cancel.create( &mlm_window, NOX("Cancel"), 250, 420, 80, 40 );
	mlm_cancel.set_hotkey( KEY_ESC );

	mlm_mission_list.create( &mlm_window, 450, 150, 150, 200, mlm_nfiles, mlm_missions );

	for ( i = 0; i < Num_recent_missions; i++ ) {
		recent_missions[i] = Recent_missions[i];
	}
	recent_mission_list.create( &mlm_window, 250, 150, 150, 200, Num_recent_missions, recent_missions );

	mlm_mission_list.set_focus();
	mlm_mission_list.set_current(0);


	mission_campaign_build_list(0);
	for ( i = 0; i < Num_campaigns; i++ ) {
		strcpy_s(Campaign_name_list[i+1], Campaign_names[i]);
	}
	strcpy_s(Campaign_name_list[0], NOX("All campaigns"));
	strcpy_s(Campaign_name_list[1], NOX("Player Missions"));

	for ( i = 0; i < Num_campaigns+2; i++ ) {
		campaign_names[i] = Campaign_name_list[i];
	}

	campaign_filter.create( &mlm_window, 50, 150, 150, 200, Num_campaigns+2, campaign_names );
	Campaign_filter_index = 0;
	campaign_filter.set_current(Campaign_filter_index);
}
