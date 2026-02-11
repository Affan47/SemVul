mapimg_create(struct mapdef *pmapdef, bool force, const char *savename,
                   const char *path)
{
  struct img *pimg;
  char mapimgfile[MAX_LEN_PATH];
  bool ret = TRUE;
#ifdef DEBUG
  struct timer *timer_cpu, *timer_user;
#endif

  if (map_is_empty()) {
    MAPIMG_LOG(_("map not yet created"));

    return FALSE;
  }

  mapimg_checkplayers(pmapdef, FALSE);

  if (pmapdef->status != MAPIMG_STATUS_OK) {
    MAPIMG_LOG(_("map definition not checked or error"));
    return FALSE;
  }


  if (!force && game.info.turn != 0
      && !(pmapdef->turns != 0 && game.info.turn % pmapdef->turns == 0)) {
    return TRUE;
  }

#ifdef DEBUG
  timer_cpu = new_timer_start(TIMER_CPU, TIMER_ACTIVE);
  timer_user = new_timer_start(TIMER_USER, TIMER_ACTIVE);
#endif


  switch (pmapdef->player.show) {
  case SHOW_PLRNAME:
  case SHOW_PLRID:
  case SHOW_NONE:
  case SHOW_ALL:
  case SHOW_PLRBV:
    generate_save_name(savename, mapimgfile, sizeof(mapimgfile),
                       mapimg_generate_name(pmapdef));

    pimg = img_new(pmapdef, CURRENT_TOPOLOGY, map.xsize, map.ysize);
    img_createmap(pimg);
    if (!img_save(pimg, mapimgfile, path)) {
      ret = FALSE;
    }
    img_destroy(pimg);
    break;
  case SHOW_EACH:
  case SHOW_HUMAN:
    players_iterate(pplayer) {
      if (!pplayer->is_alive || (pmapdef->player.show == SHOW_HUMAN
                                 && pplayer->ai_controlled)) {


        continue;
      }

      BV_CLR_ALL(pmapdef->player.checked_plrbv);
      BV_SET(pmapdef->player.checked_plrbv, player_index(pplayer));

      generate_save_name(savename, mapimgfile, sizeof(mapimgfile),
                         mapimg_generate_name(pmapdef));

      pimg = img_new(pmapdef, CURRENT_TOPOLOGY, map.xsize, map.ysize);
      img_createmap(pimg);
      if (!img_save(pimg, mapimgfile, path)) {
        ret = FALSE;
      }
      img_destroy(pimg);

      if (!ret) {
        break;
      }
    } players_iterate_end;
    break;
  }

#ifdef DEBUG
  log_debug("Image generation time: %g seconds (%g apparent)",
            read_timer_seconds(timer_cpu),
            read_timer_seconds(timer_user));

  free_timer(timer_cpu);
  free_timer(timer_user);
#endif

  return ret;
}
