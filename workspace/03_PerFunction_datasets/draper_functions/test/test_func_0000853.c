Cmd_Radio_power_f (edict_t * ent)
{
	if (!teamplay->value)
	{
		if (!((int) (dmflags->value) & (DF_MODELTEAMS | DF_SKINTEAMS)))
			return;
	}

	ent->client->resp.radio_power_off = !ent->client->resp.radio_power_off;

	if (ent->client->resp.radio_power_off)
	{
		gi.centerprintf (ent, "Radio switched off");
		unicastSound(ent, globalRadio[RADIO_CLICK].sndIndex, 1.0);
	}
	else
	{
		gi.centerprintf (ent, "Radio switched on");
		unicastSound(ent, globalRadio[RADIO_CLICK].sndIndex, 1.0);
	}
}
