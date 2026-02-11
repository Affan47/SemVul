lj_meta_cache(GCtab *mt, MMS mm, GCstr *name)
{
  cTValue *mo = lj_tab_getstr(mt, name);
  lua_assert(mm <= MM_FAST);
  if (!mo || tvisnil(mo)) {
    mt->nomm |= (uint8_t)(1u<<mm);
    return NULL;
  }
  return mo;
}
