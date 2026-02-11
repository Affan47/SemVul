objc_map_set_maximum_load_factor (objc_map_t map, int number_between_zero_and_one_hundred)
{
  if (map->number_of_non_empty_slots != 0)
    return;

  map->maximum_load_factor = number_between_zero_and_one_hundred;
  map->max_number_of_non_empty_slots = (map->number_of_slots * number_between_zero_and_one_hundred) / 100;
}
