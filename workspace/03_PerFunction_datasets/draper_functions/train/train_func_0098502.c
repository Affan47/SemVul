fizmo_free_blorb_map(z_blorb_map *blorb_map)
{
  int i = 0;
  fizmo_blorb_map *map;
  fizmo_blorb *blorb;

  if (blorb_map == NULL)
    return -1;

  map = (fizmo_blorb_map*)blorb_map->blorb_map_implementation;

  blorb = map->blorbs[i++];
  while (blorb != NULL)
  {
    free(blorb);
    blorb = map->blorbs[i++];
  }

  free(map->blorbs);
  free(map);
  free(blorb_map);

  return 0;
}
