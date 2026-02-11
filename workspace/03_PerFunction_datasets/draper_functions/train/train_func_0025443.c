bullet_array_ctor(lua_State *L)
{
	int i;
	for (i = 0; i < lua_objlen(L, 1) && i < MAXBULLETS; i++) {
		lua_rawgeti(L, 1, i+1);
		read_bullet(L, -1, &AllBullets[i]);
		lua_pop(L, 1);
	}

	return 0;
}
