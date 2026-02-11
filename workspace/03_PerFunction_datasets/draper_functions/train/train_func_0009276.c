update_unit_pix_label(struct unit_list *punitlist)
{
  int i;


  if (punitlist && unit_list_size(punitlist) > 0
      && C_S_OVER != client_state()) {


    struct unit *punit = unit_list_get(punitlist, 0);

    set_unit_icon(-1, punit);

    i = 0;
    unit_list_iterate(unit_tile(punit)->units, aunit) {
      if (aunit != punit) {
	if (i < num_units_below) {
	  set_unit_icon(i, aunit);
	}
	i++;
      }
    }
    unit_list_iterate_end;

    if (i > num_units_below) {
      set_unit_icons_more_arrow(TRUE);
    } else {
      set_unit_icons_more_arrow(FALSE);
      for(; i < num_units_below; i++) {
	set_unit_icon(i, NULL);
      }
    }
  } else {
    for(i=-1; i<num_units_below; i++) {
      set_unit_icon(i, NULL);
    }
    set_unit_icons_more_arrow(FALSE);
  }
}
