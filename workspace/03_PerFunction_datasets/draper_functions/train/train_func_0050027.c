Cmd_InvDrop_f (edict_t * ent)
{
	gitem_t *it;


	if(teamplay->value)
		return;


	if (ent->solid == SOLID_NOT && ent->deadflag != DEAD_DEAD)
		return;

	ValidateSelectedItem (ent);

	if (ent->client->pers.selected_item == -1)
	{
		gi.cprintf (ent, PRINT_HIGH, "No item to drop.\n");
		return;
	}

	it = &itemlist[ent->client->pers.selected_item];
	if (!it->drop)
	{
		gi.cprintf (ent, PRINT_HIGH, "Item is not dropable.\n");
		return;
	}
	it->drop (ent, it);

}
