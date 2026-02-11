total_activity(struct tile *ptile, enum unit_activity act)
{
  int total = 0;

  unit_list_iterate (ptile->units, punit)
    if (punit->activity == act) {
      total += punit->activity_count;
    }
  unit_list_iterate_end;
  return total;
}
