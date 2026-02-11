playercolor_free(void)
{
  if (game.server.plr_colors == NULL) {
    return;
  }

  if (rgbcolor_list_size(game.server.plr_colors) > 0) {
    rgbcolor_list_iterate(game.server.plr_colors, prgbcolor) {
      rgbcolor_list_remove(game.server.plr_colors, prgbcolor);
      rgbcolor_destroy(prgbcolor);
    } rgbcolor_list_iterate_end;
  };
  rgbcolor_list_destroy(game.server.plr_colors);
  game.server.plr_colors = NULL;
}
