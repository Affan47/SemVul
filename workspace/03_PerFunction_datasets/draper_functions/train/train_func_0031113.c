supported_units_activate_callback(Widget w, XtPointer client_data,
					      XtPointer call_data)
{
  struct unit *punit =
    player_unit_by_number(client_player(), (size_t) client_data);

  if (NULL != punit) {
    struct city *pcity = tile_city(unit_tile(punit));

    unit_focus_set(punit);
    if (NULL != pcity) {
      struct city_dialog *pdialog = get_city_dialog(pcity);

      if (NULL != pdialog) {
	city_dialog_update_supported_units(pdialog, 0);
      }
    }
  }

  destroy_message_dialog(w);
}
