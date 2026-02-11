G_TouchSolids (edict_t * ent)
{
	int i, num;
	edict_t *touch[MAX_EDICTS], *hit;

	num = gi.BoxEdicts (ent->absmin, ent->absmax, touch, MAX_EDICTS, AREA_SOLID);


	for (i = 0; i < num; i++)
	{
		hit = touch[i];
		if (!hit->inuse)
			continue;
		if (ent->touch)
			ent->touch (hit, ent, NULL, NULL);
		if (!ent->inuse)
			break;
	}
}
