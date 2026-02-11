unit_activity_dependencies(struct unit *punit,
				       enum unit_activity old_activity,
				       enum tile_special_type old_target)
{
  switch (punit->activity) {
  case ACTIVITY_IDLE:
    switch (old_activity) {
    case ACTIVITY_PILLAGE:
      {
        enum tile_special_type prereq =
	  get_infrastructure_prereq(old_target);
        if (prereq != S_LAST) {
          unit_list_iterate (unit_tile(punit)->units, punit2)
            if ((punit2->activity == ACTIVITY_PILLAGE) &&
                (punit2->activity_target == prereq)) {
              set_unit_activity(punit2, ACTIVITY_IDLE);
              send_unit_info(NULL, punit2);
            }
          unit_list_iterate_end;
        }
        break;
      }
    case ACTIVITY_EXPLORE:

      punit->ai_controlled = FALSE;
      break;
    default:
      ;
    }
    break;
  case ACTIVITY_EXPLORE:
    punit->ai_controlled = TRUE;
    set_unit_activity(punit, ACTIVITY_EXPLORE);
    send_unit_info(NULL, punit);
    break;
  default:

    break;
  }
}
