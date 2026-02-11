sim_room_campaign_mission_filter(char *filename)
{
	int num;

	num = mission_campaign_get_mission_list(filename, &Campaign_missions[Num_campaign_missions], MAX_MISSIONS - Num_campaign_missions);
	if (num < 0)
		return 0;

	Num_campaigns++;
	Num_campaign_missions += num;
	return 1;
}
