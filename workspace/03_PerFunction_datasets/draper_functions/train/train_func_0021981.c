reports_menu_callback(Widget w, XtPointer client_data,
				  XtPointer garbage)
{
  size_t pane_num = (size_t)client_data;

  switch(pane_num) {
   case MENU_REPORT_CITIES:
    city_report_dialog_popup(FALSE);
    break;
   case MENU_REPORT_UNITS:
    units_report_dialog_popup(FALSE);
    break;
  case MENU_REPORT_PLAYERS:
    popup_players_dialog(FALSE);
    break;
   case MENU_REPORT_ECONOMY:
    economy_report_dialog_popup(FALSE);
    break;
   case MENU_REPORT_SCIENCE:
    science_report_dialog_popup(FALSE);
    break;
   case MENU_REPORT_WOW:
    send_report_request(REPORT_WONDERS_OF_THE_WORLD);
    break;
   case MENU_REPORT_TOP_CITIES:
    send_report_request(REPORT_TOP_5_CITIES);
    break;
  case MENU_REPORT_MESSAGES:
    meswin_dialog_popup(FALSE);
    break;
   case MENU_REPORT_DEMOGRAPHIC:
    send_report_request(REPORT_DEMOGRAPHIC);
    break;
   case MENU_REPORT_SPACESHIP:
    if (NULL != client.conn.playing) {
      popup_spaceship_dialog(client.conn.playing);
    }
    break;
  }
}
