diplomat_keep_moving_callback(Widget w, XtPointer client_data,
					  XtPointer call_data)
{
  struct unit *punit;
  struct city *pcity;

  destroy_message_dialog(w);
  diplomat_dialog = NULL;

  if ((punit = game_unit_by_number(diplomat_id))
      && (pcity = game_city_by_number(diplomat_target_id))
      && !same_pos(unit_tile(punit), city_tile(pcity))) {
    request_diplomat_action(DIPLOMAT_MOVE, diplomat_id,
                            diplomat_target_id, 0);
  }
  process_diplomat_arrival(NULL, 0);
}
