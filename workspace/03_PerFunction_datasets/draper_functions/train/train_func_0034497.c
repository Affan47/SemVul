slapi_mods_get_next_smod(Slapi_Mods *smods, Slapi_Mod *smod)
{
	LDAPMod *mod = slapi_mods_get_next_mod(smods);

	if (mod == NULL)
	{
		return NULL;
	}
	else
	{
		mod2smod(mod, smod);
	}
	return smod;
}
