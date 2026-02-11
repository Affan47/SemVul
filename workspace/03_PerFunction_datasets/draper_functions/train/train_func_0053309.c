add_unit_to_battlegroup(int battlegroup)
{
  if (NULL != client.conn.playing && can_client_issue_orders()) {
    struct unit *punit;

    punit = head_of_units_in_focus();
    if (punit && punit->battlegroup == battlegroup) {

      unit_change_battlegroup(punit, BATTLEGROUP_NONE);
      refresh_unit_mapcanvas(punit, unit_tile(punit), TRUE, FALSE);
    } else {
      key_unit_assign_battlegroup(battlegroup, TRUE);
    }
  }
}
