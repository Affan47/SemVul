map_show_circle(struct player *pplayer, struct tile *ptile, int radius_sq)
{
  buffer_shared_vision(pplayer);

  circle_iterate(ptile, radius_sq, tile1) {
    map_show_tile(pplayer, tile1);
  } circle_iterate_end;

  unbuffer_shared_vision(pplayer);
}
