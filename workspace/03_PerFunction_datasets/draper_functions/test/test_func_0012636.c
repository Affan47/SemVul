ChangeWeapon (edict_t * ent)
{

	if (ent->client->grenade_time)
	{
		ent->client->grenade_time = level.time;
		ent->client->weapon_sound = 0;
		weapon_grenade_fire (ent, false);
		ent->client->grenade_time = 0;
	}

	if(ent->client->ctf_grapple)
		CTFPlayerResetGrapple(ent);


	ent->client->reload_attempts = 0;

	ent->client->pers.lastweapon = ent->client->pers.weapon;
	ent->client->pers.weapon = ent->client->newweapon;
	ent->client->newweapon = NULL;
	ent->client->machinegun_shots = 0;

	if (ent->client->pers.weapon && ent->client->pers.weapon->ammo)
		ent->client->ammo_index = ITEM_INDEX (FindItem (ent->client->pers.weapon->ammo));
	else
		ent->client->ammo_index = 0;

	if (!ent->client->pers.weapon || ent->s.modelindex != 255)
	{
		ent->client->ps.gunindex = 0;
		return;
	}

	ent->client->weaponstate = WEAPON_ACTIVATING;
	ent->client->ps.gunframe = 0;


	if (ent->solid == SOLID_NOT && ent->deadflag != DEAD_DEAD)
		return;


	ent->client->ps.gunindex = gi.modelindex (ent->client->pers.weapon->view_model);


	ent->client->anim_priority = ANIM_PAIN;
	if (ent->client->ps.pmove.pm_flags & PMF_DUCKED)
	{
		ent->s.frame = FRAME_crpain1;
		ent->client->anim_end = FRAME_crpain4;
	}
	else
	{
		ent->s.frame = FRAME_pain301;
		ent->client->anim_end = FRAME_pain304;
	}

	ShowGun (ent);


	switch(ent->client->pers.weapon->typeNum) {
	case MK23_NUM:
	case MP5_NUM:
	case M4_NUM:
	case M3_NUM:
	case HC_NUM:
	case SNIPER_NUM:
	case DUAL_NUM:
	case KNIFE_NUM:
	case GRAPPLE_NUM:
		ent->client->curr_weap = ent->client->pers.weapon->typeNum;
		break;
	case GRENADE_NUM:

		if (teamplay->value && INV_AMMO(ent, GRENADE_NUM) == 0)
			INV_AMMO(ent, GRENADE_NUM) = 1;

		ent->client->curr_weap = ent->client->pers.weapon->typeNum;
		break;
    }

	if (INV_AMMO(ent, LASER_NUM))
		SP_LaserSight (ent, GET_ITEM(LASER_NUM));
}
