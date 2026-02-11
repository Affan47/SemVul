shared_vision_change_seen(struct player *pplayer,
                                      struct tile *ptile,
                                      const v_radius_t change,
                                      bool can_reveal_tiles)
{
  map_change_own_seen(pplayer, ptile, change);
  map_change_seen(pplayer, ptile, change, can_reveal_tiles);

  players_iterate(pplayer2) {
    if (really_gives_vision(pplayer, pplayer2)) {
      map_change_seen(pplayer2, ptile, change, can_reveal_tiles);
    }
  } players_iterate_end;
}
