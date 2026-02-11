units_can_unload(const struct unit_list *punits)
{
  unit_list_iterate(punits, punit) {
    if (unit_transported(punit)
        && can_unit_unload(punit, unit_transport_get(punit))
        && can_unit_exist_at_tile(punit, unit_tile(punit))) {
      return TRUE;
    }
  } unit_list_iterate_end;

  return FALSE;
}
