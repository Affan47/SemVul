CleanLevel ()
{
	char *remove_classnames[] = {
		"weapon_Mk23",
		"weapon_MP5",
		"weapon_M4",
		"weapon_M3",
		"weapon_HC",
		"weapon_Sniper",
		"weapon_Dual",
		"weapon_Knife",
		"weapon_Grenade",
		"ammo_sniper",
		"ammo_clip",
		"ammo_mag",
		"ammo_m4",
		"ammo_m3",
		"item_quiet",
		"item_slippers",
		"item_band",
		"item_lasersight",
		"item_vest",
		"thrown_knife",
		"hgrenade",
		"item_helmet"
	};
	int i;
	int base;
	edict_t *ent;

	base = 1 + maxclients->value + BODY_QUEUE_SIZE;
	ent = g_edicts + base;
	for (i = 1 + maxclients->value + BODY_QUEUE_SIZE; i < globals.num_edicts; i++, ent++)
	{
		if (!ent->classname)
			continue;
		if (member_array (ent->classname, remove_classnames,
			sizeof (remove_classnames) / sizeof (char *)) > -1)
		{
			G_FreeEdict (ent);
		}
	}

	CleanBodies ();


	CGF_SFX_RebuildAllBrokenGlass ();
}
