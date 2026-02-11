can_unit_paradrop(const struct unit *punit)
{
  struct unit_type *utype;

  if (!unit_has_type_flag(punit, F_PARATROOPERS))
    return FALSE;

  if(punit->paradropped)
    return FALSE;

  utype = unit_type(punit);

  if(punit->moves_left < utype->paratroopers_mr_req)
    return FALSE;

  if (tile_has_base_flag(unit_tile(punit), BF_PARADROP_FROM)) {


    return TRUE;
  }

  if (!tile_city(unit_tile(punit))) {
    return FALSE;
  }

  return TRUE;
}
