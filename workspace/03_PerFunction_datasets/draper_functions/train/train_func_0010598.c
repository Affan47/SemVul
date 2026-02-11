can_unit_survive_at_tile(const struct unit *punit,
                              const struct tile *ptile)
{
  if (!can_unit_exist_at_tile(punit, ptile)) {
    return FALSE;
  }

  if (tile_city(ptile)) {
    return TRUE;
  }

  if (tile_has_native_base(ptile, unit_type(punit))) {

    return TRUE;
  }

  if (utype_fuel(unit_type(punit))) {

    return FALSE;
  }

  if (is_losing_hp(punit)) {

    return FALSE;
  }

  return TRUE;
}
