unit_can_defend_here(const struct unit *punit)
{
  struct unit *ptrans = unit_transport_get(punit);


  return (can_unit_exist_at_tile(punit, unit_tile(punit))
          && (ptrans == NULL || can_unit_unload(punit, ptrans)));
}
