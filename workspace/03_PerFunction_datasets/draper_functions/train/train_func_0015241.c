city_specialists(const struct city *pcity)
{
  citizens count = 0;

  specialist_type_iterate(sp) {
    fc_assert_ret_val(MAX_CITY_SIZE - count > pcity->specialists[sp], 0);
    count += pcity->specialists[sp];
  } specialist_type_iterate_end;

  return count;
}
