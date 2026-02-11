Cmd_Statmode_f(edict_t* ent, char *arg)
{
	int i;
	char stuff[32];


	if (!arg[0])
		return;


	i = atoi (arg);

	if (i > 2 || i < 0) {
		gi.dprintf("Warning: stat_mode set to %i by %s\n", i, ent->client->pers.netname);


		if (ent->client->resp.stat_mode > 0 && ent->client->resp.stat_mode < 3)
			sprintf(stuff, "set stat_mode \"%i\"\n", ent->client->resp.stat_mode);
		else
			sprintf(stuff, "set stat_mode \"0\"\n");
	} else {
		sprintf(stuff, "set stat_mode \"%i\"\n", i);
		ent->client->resp.stat_mode = i;
	}
	stuffcmd(ent, stuff);
}
