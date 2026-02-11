lj_meta_len(lua_State *L, cTValue *o)
{
  cTValue *mo = lj_meta_lookup(L, o, MM_len);
  if (tvisnil(mo)) {
    if (LJ_52 && tvistab(o))
      tabref(tabV(o)->metatable)->nomm |= (uint8_t)(1u<<MM_len);
    else
      lj_err_optype(L, o, LJ_ERR_OPLEN);
    return NULL;
  }
  return mmcall(L, lj_cont_ra, mo, o, LJ_52 ? o : niltv(L));
}
