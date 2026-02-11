del_graphics_player_info(Graphics_player_info *pinfo) {
  int x;
  free(pinfo->name);
  del_vector(pinfo->place);
  for (x = 0 ; x < OT_NRFOOD; x++) {
    if (pinfo->foodcaches[x] != NULL) {
      del_graphics_cache(pinfo->foodcaches[x]);
    }
  }
  if (pinfo->name_graphic != NULL) {
    SDL_FreeSurface(pinfo->name_graphic);
  }
  free(pinfo);
}
