Cmd_PutAway_f (edict_t * ent)
{
	ent->client->showscores = false;
	ent->client->showhelp = false;
	ent->client->showinventory = false;

	if (ent->client->menu)
		PMenu_Close (ent);

}
