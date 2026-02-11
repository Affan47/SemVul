SetWeaponModeFunc(void *_self)
{
	menulist_s *self;
	int i, value;

	self = (menulist_s*)_self;

	value = self->curvalue;

	if (self->curvalue)
	{
		for (i = 0; i < num_weapon_modes; i++)
		{
			Cvar_SetValue (weaponModeNames[i][1], 0);
			s_weaponmode_list[i].curvalue = 0;
		}
	}

	Cvar_SetValue (self->generic.localstrings[0], value);
	self->curvalue = value;
}
