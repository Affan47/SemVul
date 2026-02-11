Pickup_Armor (edict_t * ent, edict_t * other)
{
	int old_armor_index;
	gitem_armor_t *oldinfo;
	gitem_armor_t *newinfo;
	int newcount;
	float salvage;
	int salvagecount;


	newinfo = (gitem_armor_t *) ent->item->info;

	old_armor_index = ArmorIndex (other);


	if (ent->item->tag == ARMOR_SHARD)
	{
		if (!old_armor_index)
			other->client->pers.inventory[jacket_armor_index] = 2;
		else
			other->client->pers.inventory[old_armor_index] += 2;
	}

	else if (!old_armor_index)
	{
		other->client->pers.inventory[ITEM_INDEX (ent->item)] =
		newinfo->base_count;
	}

	else
	{

		if (old_armor_index == jacket_armor_index)
			oldinfo = &jacketarmor_info;
		else if (old_armor_index == combat_armor_index)
			oldinfo = &combatarmor_info;
		else
			oldinfo = &bodyarmor_info;

		if (newinfo->normal_protection > oldinfo->normal_protection)
		{

			salvage = oldinfo->normal_protection / newinfo->normal_protection;
			salvagecount =
			salvage * other->client->pers.inventory[old_armor_index];
			newcount = newinfo->base_count + salvagecount;
			if (newcount > newinfo->max_count)
				newcount = newinfo->max_count;


			other->client->pers.inventory[old_armor_index] = 0;


			other->client->pers.inventory[ITEM_INDEX (ent->item)] = newcount;
		}
		else
		{

			salvage = newinfo->normal_protection / oldinfo->normal_protection;
			salvagecount = salvage * newinfo->base_count;
			newcount =
			other->client->pers.inventory[old_armor_index] + salvagecount;
			if (newcount > oldinfo->max_count)
				newcount = oldinfo->max_count;


			if (other->client->pers.inventory[old_armor_index] >= newcount)
				return false;


			other->client->pers.inventory[old_armor_index] = newcount;
		}
	}

	if (!(ent->spawnflags & DROPPED_ITEM) && (deathmatch->value))
		SetRespawn (ent, 20);

	return true;
}
