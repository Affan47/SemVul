transfer_city_units(struct player *pplayer, struct player *pvictim,
			 struct unit_list *units, struct city *pcity,
			 struct city *exclude_city,
			 int kill_outside, bool verbose)
{
  struct tile *ptile = pcity->tile;
  int saved_id = pcity->id;
  const char *name = city_name(pcity);


  if (pplayer != pvictim) {
    unit_list_iterate_safe((ptile)->units, vunit)  {

      if (unit_owner(vunit) == pvictim) {


	transfer_unit(vunit, pcity, verbose);
	unit_list_remove(units, vunit);
      } else if (!pplayers_allied(pplayer, unit_owner(vunit))) {

        bounce_unit(vunit, verbose);
      }
    } unit_list_iterate_safe_end;
  }

  if (!city_exist(saved_id)) {
    saved_id = 0;
  }


  unit_list_iterate_safe(units, vunit) {
    struct city *new_home_city = tile_city(unit_tile(vunit));
    if (new_home_city && new_home_city != exclude_city
	&& city_owner(new_home_city) == unit_owner(vunit)) {


      transfer_unit(vunit, new_home_city, verbose);
    } else if ((kill_outside == -1
                || real_map_distance(unit_tile(vunit), ptile) <= kill_outside)
               && saved_id) {

      transfer_unit(vunit, pcity, verbose);
      if (unit_tile(vunit) == ptile && !pplayers_allied(pplayer, pvictim)) {

        bounce_unit(vunit, TRUE);
      }
    } else {


      log_verbose("Lost %s %s at (%d,%d) when %s was lost.",
                  nation_rule_name(nation_of_unit(vunit)),
                  unit_rule_name(vunit), TILE_XY(unit_tile(vunit)), name);
      if (verbose) {
        notify_player(unit_owner(vunit), unit_tile(vunit),
                      E_UNIT_LOST_MISC, ftc_server,
                      _("%s lost along with control of %s."),
                      unit_tile_link(vunit), name);
      }
      wipe_unit(vunit, ULR_CITY_LOST, NULL);
    }
  } unit_list_iterate_safe_end;

#ifdef DEBUG
  unit_list_iterate(pcity->units_supported, punit) {
    fc_assert(punit->homecity == pcity->id);
    fc_assert(unit_owner(punit) == pplayer);
  } unit_list_iterate_end;
#endif
}
