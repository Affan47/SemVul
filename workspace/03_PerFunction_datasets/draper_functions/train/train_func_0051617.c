get_bittab_and_bit(lua_State *L, GtBittab ***bittab, long *bit)
{
  *bittab = check_bittab(L, 1);
  *bit = luaL_checklong(L, 2);
  luaL_argcheck(L, *bit >= 0, 2, "bit number too small");
  luaL_argcheck(L, *bit < gt_bittab_size(**bittab), 2, "bit number too large");
}
