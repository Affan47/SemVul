SelectPrevItem (edict_t * ent, int itflags)
{
	gclient_t *cl;
	int i, index;
	gitem_t *it;

	cl = ent->client;


	if (cl->menu)
	{
		PMenu_Prev (ent);
		return;
	}


	if (ent->solid == SOLID_NOT && ent->deadflag != DEAD_DEAD)
		return;


	for (i = 1; i <= MAX_ITEMS; i++)
	{
		index = (cl->pers.selected_item + MAX_ITEMS - i) % MAX_ITEMS;
		if (!cl->pers.inventory[index])
			continue;
		it = &itemlist[index];
		if (!it->use)
			continue;
		if (!(it->flags & itflags))
			continue;

		cl->pers.selected_item = index;
		return;
	}

	cl->pers.selected_item = -1;
}
