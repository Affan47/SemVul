ClearPlayer(int id)
{
	player[id].used = 0;
	player[id].client_number = 0;
	player[id].server_number = 0;
	player[id].lastpacket = 0;
	player[id].joinstatus = 0;

	free(player[id].name);
	player[id].name = NULL;
	free(player[id].spraylogo);
	player[id].spraylogo = NULL;
	free(player[id].win);
	player[id].win = NULL;
	player[id].usgn = 0;
	player[id].version = 0;

	player[id].team = 0;
	player[id].deaths = 0;
	player[id].score = 0;

	player[id].x = &lcbuffer[0][id-1][0];
	player[id].y = &lcbuffer[0][id-1][1];

	player[id].health = 0;
	player[id].armor = 0;

	player[id].actualweapon = 0;
	player[id].reloading = 0;
	player[id].reloadtimer = 0;
	player[id].zoomtimer = 0;
	player[id].firetimer = 0;
	player[id].rcon = 0;

	int i;
	for (i = 0; i <= 0xFF; i++)
	{
		player[id].wpntable[i].status = 0;
		player[id].wpntable[i].ammo1 = 0;
		player[id].wpntable[i].ammo2 = 0;
	}
	for (i = 0; i < LC_BUFFER_SIZE; i++)
	{
		lcbuffer[i][id-1][0] = 0;
		lcbuffer[i][id-1][1] = 0;
	}
	player[id].rotation = 0;

	player[id].dead = 1;

	player[id].start = 0;
	player[id].money = mp_startmoney;


	player[id].spray_payload = NULL;
	player[id].spray_payload_size = 0;

	player[id].spray_data = NULL;
	player[id].spray_data_size = 0;


	player[id].port = 0;

}
