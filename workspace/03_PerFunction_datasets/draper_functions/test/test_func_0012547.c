undeploy_buttons(Gameboard *g, void (*callback)(Gameboard *ptr)){

  if(g->b.buttons_ready){

    button_clear_state(g);
    g->b.buttons_ready=0;


    g->b.sweeper  = 0;
    g->b.sweeperd = -1;

    g->button_callback = callback;
    if(g->button_timer!=0)
      g_source_remove(g->button_timer);
    g->button_timer = g_timeout_add(BUTTON_ANIM_INTERVAL, animate_button_frame, (gpointer)g);
  }else
    callback(g);

}
