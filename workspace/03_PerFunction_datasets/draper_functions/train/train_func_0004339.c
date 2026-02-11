goto_cmd_callback(GtkWidget *dlg, gint arg)
{
  switch (arg) {
  case GTK_RESPONSE_CANCEL:
    center_tile_mapcanvas(original_tile);
    break;

  case CMD_AIRLIFT:
    {
      struct city *pdestcity = get_selected_city();

      if (pdestcity) {
        unit_list_iterate(get_units_in_focus(), punit) {
          if (unit_can_airlift_to(punit, pdestcity)) {
            request_unit_airlift(punit, pdestcity);
          }
        } unit_list_iterate_end;
      }
    }
    break;

  case CMD_GOTO:
    {
      struct city *pdestcity = get_selected_city();

      if (pdestcity) {
	unit_list_iterate(get_units_in_focus(), punit) {
          send_goto_tile(punit, pdestcity->tile);
        } unit_list_iterate_end;
      }
    }
    break;

  default:
    break;
  }

  gtk_widget_destroy(dlg);
  dshell = NULL;
}
