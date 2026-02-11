show_game_page()
{
  struct widget *pWidget;
  SDL_Surface *pIcon_theme = NULL;

  if (SDL_Client_Flags & CF_MAP_UNIT_W_CREATED) {
    return;
  }

  popup_minimap_window();
  popup_unitinfo_window();
  SDL_Client_Flags |= CF_MAP_UNIT_W_CREATED;

  #ifndef SMALL_SCREEN
  init_options_button();
  #endif


  pIcon_theme = adj_surf(GET_SURF(client_cooling_sprite()));
  fc_assert(pIcon_theme != NULL);
  pWidget = create_iconlabel(pIcon_theme, Main.gui, NULL, WF_FREE_THEME);

#ifdef SMALL_SCREEN
  widget_set_position(pWidget,
                      pWidget->dst->surface->w - pWidget->size.w - adj_size(10),
                      0);
#else
  widget_set_position(pWidget,
                      pWidget->dst->surface->w - pWidget->size.w - adj_size(10),
                      adj_size(10));
#endif

  add_to_gui_list(ID_COOLING_ICON, pWidget);


  pIcon_theme = adj_surf(GET_SURF(client_warming_sprite()));
  fc_assert(pIcon_theme != NULL);

  pWidget = create_iconlabel(pIcon_theme, Main.gui, NULL, WF_FREE_THEME);

#ifdef SMALL_SCREEN
  widget_set_position(pWidget,
                      pWidget->dst->surface->w - pWidget->size.w * 2 - adj_size(10),
                      0);
#else
  widget_set_position(pWidget,
                      pWidget->dst->surface->w - pWidget->size.w * 2 - adj_size(10),
                      adj_size(10));
#endif

  add_to_gui_list(ID_WARMING_ICON, pWidget);


  create_units_order_widgets();


  enable_options_button();
  enable_order_buttons();
}
