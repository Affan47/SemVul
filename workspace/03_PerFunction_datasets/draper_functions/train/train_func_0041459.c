unit_focus_add(struct unit *punit)
{
  if (NULL != punit
      && NULL != client.conn.playing
      && unit_owner(punit) != client.conn.playing) {

    return;
  }

  if (NULL == punit || !can_client_change_view()) {
    return;
  }

  if (unit_is_in_focus(punit)) {
    return;
  }

  if (hover_state != HOVER_NONE) {


    set_hover_state(NULL, HOVER_NONE, ACTIVITY_LAST, ORDER_LAST);
  }

  current_focus_append(punit);
  focus_units_changed();
}
