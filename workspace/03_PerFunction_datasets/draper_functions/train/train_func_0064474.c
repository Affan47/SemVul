can_player_build_improvement_direct(const struct player *p,
					 struct impr_type *pimprove)
{
  bool space_part = FALSE;

  if (!valid_improvement(pimprove)) {
    return FALSE;
  }

  requirement_vector_iterate(&pimprove->reqs, preq) {
    if (preq->range >= REQ_RANGE_PLAYER
        && !is_req_active(p, NULL, NULL, NULL, NULL, NULL, NULL, preq,
                          RPT_CERTAIN)) {
      return FALSE;
    }
  } requirement_vector_iterate_end;


  if (building_has_effect(pimprove, EFT_SS_STRUCTURAL)) {
    space_part = TRUE;
    if (p->spaceship.structurals >= NUM_SS_STRUCTURALS) {
      return FALSE;
    }
  }
  if (building_has_effect(pimprove, EFT_SS_COMPONENT)) {
    space_part = TRUE;
    if (p->spaceship.components >= NUM_SS_COMPONENTS) {
      return FALSE;
    }
  }
  if (building_has_effect(pimprove, EFT_SS_MODULE)) {
    space_part = TRUE;
    if (p->spaceship.modules >= NUM_SS_MODULES) {
      return FALSE;
    }
  }
  if (space_part &&
      (!get_player_bonus(p, EFT_ENABLE_SPACE) > 0
       || p->spaceship.state >= SSHIP_LAUNCHED)) {
    return FALSE;
  }

  if (is_great_wonder(pimprove)) {

    if (!great_wonder_is_available(pimprove)) {
      return FALSE;
    }
  }

  return TRUE;
}
