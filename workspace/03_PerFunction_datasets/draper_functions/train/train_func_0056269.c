lua_event_get_skill(lua_State * L)
{
	const char *skilltype = luaL_checkstring(L, 1);
	int *skillptr = NULL;
	if (!strcmp(skilltype, "melee")) {
		skillptr = &Me.melee_weapon_skill;
	} else if (!strcmp(skilltype, "ranged")) {
		skillptr = &Me.ranged_weapon_skill;
	} else if (!strcmp(skilltype, "programming")) {
		skillptr = &Me.spellcasting_skill;
	} else {
		ErrorMessage(__FUNCTION__,
			     "Lua script called me with an incorrect parameter. Accepted values are \"melee\", \"ranged\", and \"programming\".\n",
			     PLEASE_INFORM, IS_WARNING_ONLY);
	}

	if (skillptr) {
		lua_pushinteger(L, *skillptr);
	} else
		lua_pushinteger(L, 0);

	return 1;
}
