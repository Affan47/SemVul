set_unit_reserv (reserv_sets_t reservs, int cycle_num, int unit_num)
{
  if (cycle_num >= max_cycles_num)
    abort ();
  SET_BIT (reservs, cycle_num * els_in_cycle_reserv
           * sizeof (set_el_t) * CHAR_BIT + unit_num);
}
