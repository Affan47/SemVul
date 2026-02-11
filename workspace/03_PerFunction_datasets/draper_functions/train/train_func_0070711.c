campaign_savefile_save(char *pname)
{
	if (Campaign.type == CAMPAIGN_TYPE_SINGLE)
		Game_mode &= ~GM_MULTIPLAYER;
	else
		Game_mode |= GM_MULTIPLAYER;

	strcpy_s(Player->callsign, pname);

	return (int)Pilot.save_savefile();
}
