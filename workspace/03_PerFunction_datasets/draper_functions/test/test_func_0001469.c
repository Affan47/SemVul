assign_player_colors(void)
{
  struct rgbcolor_list *spare_colors =
    rgbcolor_list_copy(game.server.plr_colors);
  int needed = player_count();

  players_iterate(pplayer) {
    const struct rgbcolor *autocolor;

    if (!pplayer->rgb
        && (autocolor = player_preferred_color(pplayer))) {
      player_set_color(pplayer, autocolor);
    }
    if (pplayer->rgb) {

      needed--;

      rgbcolor_list_iterate(spare_colors, prgbcolor) {
        if (rgbcolors_are_equal(pplayer->rgb, prgbcolor)) {
          rgbcolor_list_remove(spare_colors, prgbcolor);
        }
      } rgbcolor_list_iterate_end;
    }
  } players_iterate_end;

  if (needed == 0) {

    rgbcolor_list_destroy(spare_colors);
    return;
  }

  fc_assert(game.server.plrcolormode == PLRCOL_PLR_RANDOM
            || game.server.plrcolormode == PLRCOL_PLR_SET);

  if (needed > rgbcolor_list_size(spare_colors)) {
    log_verbose("Not enough unique colors for all players; there will be "
                "duplicates");


    rgbcolor_list_destroy(spare_colors);
    spare_colors = rgbcolor_list_copy(game.server.plr_colors);
  }


  if (needed > rgbcolor_list_size(spare_colors)) {
    int i, origsize = rgbcolor_list_size(spare_colors);

    rgbcolor_list_shuffle(spare_colors);

    for (i = origsize; i < needed; i++) {
      rgbcolor_list_append(spare_colors,
                           rgbcolor_list_get(spare_colors, i - origsize));
    }
  }

  rgbcolor_list_shuffle(spare_colors);


  players_iterate(pplayer) {
    if (!pplayer->rgb) {
      player_set_color(pplayer, rgbcolor_list_front(spare_colors));
      rgbcolor_list_pop_front(spare_colors);
    }
  } players_iterate_end;

  rgbcolor_list_destroy(spare_colors);
}
