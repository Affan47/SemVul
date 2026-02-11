transporter_for_unit(const struct unit *pcargo)
{
  struct tile *ptile = unit_tile(pcargo);

  unit_list_iterate(ptile->units, ptrans) {
    if (can_unit_load(pcargo, ptrans)) {
      return ptrans;
    }
  } unit_list_iterate_end;

  return NULL;
}
