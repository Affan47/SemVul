zxid_add_mapped_attr(zxid_conf* cf, zxid_ses* ses, zxid_entity* meta, struct zx_elem_s* father, char* lk, struct zxid_map* sp_aamap, const char* name, const char* val)
{
  struct zxid_map* map;
  map = zxid_find_map(sp_aamap, name);
  if (!map)
    map = zxid_find_map(cf->aamap, name);
  if (map && map->rule != ZXID_MAP_RULE_DEL) {
    D("%s: ATTR(%s)=VAL(%s)", lk, name, val);
    if (map->dst && *map->dst && map->src && map->src[0] != '*')
      name = map->dst;
    zxid_mk_sa_attribute_ss(cf, father, name, 0, zxid_map_val(cf, ses, meta, map, name, val));
  } else {
    D("%s: Attribute(%s) filtered out either by del rule in aamap, or does not match aamap %p", lk, name, map);
  }
}
