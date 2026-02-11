check_units_single_tile(struct tile *ptile)
{
  unit_list_iterate_safe(ptile->units, punit) {
    bool unit_alive = TRUE;

    if (unit_tile(punit) == ptile
        && !unit_transported(punit)
        && !can_unit_exist_at_tile(punit, ptile)) {

      adjc_iterate(ptile, ptile2) {
	if (can_unit_exist_at_tile(punit, ptile2)
            && !is_non_allied_unit_tile(ptile2, unit_owner(punit))
            && !is_non_allied_city_tile(ptile2, unit_owner(punit))) {
          log_verbose("Moved %s %s due to changing terrain at (%d,%d).",
                      nation_rule_name(nation_of_unit(punit)),
                      unit_rule_name(punit), TILE_XY(unit_tile(punit)));
          notify_player(unit_owner(punit), unit_tile(punit),
                        E_UNIT_RELOCATED, ftc_server,
                        _("Moved your %s due to changing terrain."),
                        unit_link(punit));
	  unit_alive = unit_move(punit, ptile2, 0);
	  if (unit_alive && punit->activity == ACTIVITY_SENTRY) {
	    unit_activity_handling(punit, ACTIVITY_IDLE);
	  }
	  break;
	}
      } adjc_iterate_end;
      if (unit_alive && unit_tile(punit) == ptile) {

        log_verbose("Disbanded %s %s due to changing land "
                    " to sea at (%d, %d).",
                    nation_rule_name(nation_of_unit(punit)),
                    unit_rule_name(punit), TILE_XY(unit_tile(punit)));
        notify_player(unit_owner(punit), unit_tile(punit),
                      E_UNIT_LOST_MISC, ftc_server,
                      _("Disbanded your %s due to changing terrain."),
                      unit_tile_link(punit));
        wipe_unit(punit, ULR_NONNATIVE_TERR, NULL);
      }
    }
  } unit_list_iterate_safe_end;
}
