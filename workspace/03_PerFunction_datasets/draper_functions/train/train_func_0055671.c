animate_level_frame(gpointer ptr){
  Gameboard *g = GAMEBOARD (ptr);
  int i;

  if(g->d.center_x == 0){
    g->d.center_done=1;
    g_source_remove(g->d.icon_timer);
    g->d.icon_timer=0;

    if(levelstate_in_progress())
      deploy_reset_button(g);

    expose_full(g);
    return 0;
  }

  g->d.center_done=0;
  for(i=0;i<5;i++)
    if(g->d.level_icons[i].alpha)
      invalidate_icon(g, g->d.level_icons+i);

  if(g->d.center_x < 0){
    g->d.center_x += ICON_DELTA;
    if(g->d.center_x > 0) g->d.center_x = 0;
  }else{
    g->d.center_x -= ICON_DELTA;
    if(g->d.center_x < 0) g->d.center_x = 0;
  }


  render_level_icons(g, 0, 0, 0, 0, 0);

  for(i=0;i<5;i++)
    if(g->d.level_icons[i].alpha)
      invalidate_icon(g, g->d.level_icons+i);

  return 1;
}
