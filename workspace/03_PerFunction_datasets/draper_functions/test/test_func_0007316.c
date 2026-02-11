L4D_UpdateSpectatorLights(edict_t *ent)
{
	gi.dprintf("L4D_UpdateSpectatorLight called: target: %s, mode: %d\n", (ent->client->chase_target != NULL ? "yes" : "no"), ent->client->chase_mode );

	if(ent->client->chase_target) {
		if(ent->client->chase_target->client->resp.team == TEAM1)
			L4D_ZombieLights(ent);
		else
			L4D_HumanLights(ent);
		return;
	}

	L4D_ResetLights(ent);
}
