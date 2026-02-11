fill_tile_unit_list(const struct tile *ptile, struct unit **unit_list)
{
  int i = 0;


  unit_list_iterate(ptile->units, punit) {
    unit_list[i] = punit;
    i++;
  } unit_list_iterate_end;


  qsort(unit_list, i, sizeof(*unit_list), unit_list_compare);
}
