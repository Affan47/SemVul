can_build_base(const struct unit *punit, const struct base_type *pbase,
                    const struct tile *ptile)
{
  if (tile_city(ptile)) {

    return FALSE;
  }

  if (!pbase->buildable) {

    return FALSE;
  }

  if (tile_has_base(ptile, pbase)) {

    return FALSE;
  }

  return are_reqs_active(unit_owner(punit), NULL, NULL, ptile,
                         unit_type(punit), NULL, NULL, &pbase->reqs,
                         RPT_CERTAIN);
}
