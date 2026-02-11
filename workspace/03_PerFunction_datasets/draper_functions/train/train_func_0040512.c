wakeup_sentried_units(struct tile *ptile)
{
  if (!can_client_issue_orders()) {
    return;
  }
  unit_list_iterate(ptile->units, punit) {
    if (punit->activity == ACTIVITY_SENTRY
	&& unit_owner(punit) == client.conn.playing) {
      request_new_unit_activity(punit, ACTIVITY_IDLE);
    }
  }
  unit_list_iterate_end;
}
