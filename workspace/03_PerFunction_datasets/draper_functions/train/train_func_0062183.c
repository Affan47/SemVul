ur_map_create() {
  ur_map *map=(ur_map*)turn_malloc(sizeof(ur_map));
  if(ur_map_init(map)<0) {
    turn_free(map,sizeof(ur_map));
    return NULL;
  }
  return map;
}
