main_key_down_handler(SDL_keysym Key, void *pData)
{
  static struct widget *pWidget;
  if ((pWidget = find_next_widget_for_key(NULL, Key)) != NULL) {
    return widget_pressed_action(pWidget);
  } else {
    if (Key.sym == SDLK_TAB) {

      popup_input_line();
    } else {
      if (map_event_handler(Key)
		&& C_S_RUNNING == client_state()) {
        switch (Key.sym) {
	  case SDLK_RETURN:
	  case SDLK_KP_ENTER:
            if (LSHIFT || RSHIFT) {
	      disable_focus_animation();
	      key_end_turn();
            } else {
              struct unit *pUnit;
              struct city *pCity;
              if (NULL != (pUnit = head_of_units_in_focus()) &&
                (pCity = tile_city(unit_tile(pUnit))) != NULL &&
                city_owner(pCity) == client.conn.playing) {
                popup_city_dialog(pCity);
              }
	    }
          return ID_ERROR;

          case SDLK_F2:
            units_report_dialog_popup(FALSE);
          return ID_ERROR;

          case SDLK_F4:
            city_report_dialog_popup(FALSE);
            return ID_ERROR;

	  case SDLK_F7:
            send_report_request(REPORT_WONDERS_OF_THE_WORLD);
          return ID_ERROR;

          case SDLK_F8:
            send_report_request(REPORT_TOP_5_CITIES);
          return ID_ERROR;

          case SDLK_F9:
            if (meswin_dialog_is_open()) {
              meswin_dialog_popdown();
            } else {
              meswin_dialog_popup(TRUE);
            }
            flush_dirty();
            return ID_ERROR;

	  case SDLK_F11:
            send_report_request(REPORT_DEMOGRAPHIC);
          return ID_ERROR;

	  case SDLK_F12:
            popup_spaceship_dialog(client.conn.playing);
          return ID_ERROR;

	  default:
	  return ID_ERROR;
	}
      }
    }
  }

  return ID_ERROR;
}
