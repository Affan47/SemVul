mission_campaign_previous_mission()
{
	if ( !(Game_mode & GM_CAMPAIGN_MODE) )
		return 0;

	if ( Campaign.prev_mission == -1 )
		return 0;

	Campaign.current_mission = Campaign.prev_mission;
	Campaign.next_mission = Campaign.current_mission;
	Campaign.num_missions_completed--;
	Campaign.missions[Campaign.next_mission].completed = 0;

	Pilot.save_savefile();


	memcpy( &Player->stats, &Campaign.missions[Campaign.current_mission].stats, sizeof(Player->stats) );

	strncpy( Game_current_mission_filename, Campaign.missions[Campaign.current_mission].name, MAX_FILENAME_LEN );
	Num_granted_ships = 0;
	Num_granted_weapons = 0;

	return 1;
}
