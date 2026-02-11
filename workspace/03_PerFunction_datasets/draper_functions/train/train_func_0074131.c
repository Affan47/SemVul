CTFCheckHurtCarrier(edict_t * targ, edict_t * attacker)
{
	gitem_t *flag_item;

	if (!targ->client || !attacker->client)
		return;

	if (targ->client->resp.team == TEAM1)
		flag_item = flag2_item;
	else
		flag_item = flag1_item;

	if (targ->client->pers.inventory[ITEM_INDEX(flag_item)] &&
	    targ->client->resp.team != attacker->client->resp.team)
		attacker->client->resp.ctf_lasthurtcarrier = level.time;
}
