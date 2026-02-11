s48_allocate_weakAgc(long len_in_bytes) {
  Area* area = creation_space.weaks;
  s48_address result;

  if (AREA_REMAINING(area) < len_in_bytes) {
    if (gc_forbid_count == 0) {
      s48_collect(FALSE);
      area = creation_space.weaks;
    }
    else {
      Area** areap = &generations[0].current_space->weaks_area;
      if (AREA_REMAINING(*areap) < len_in_bytes) {
	Area* new_area = s48_allocate_area(S48_MINIMUM_WEAK_AREA_SIZE,
					   S48_MAXIMUM_WEAK_AREA_SIZE,
					   0, AREA_TYPE_SIZE_WEAKS);
	new_area->next = *areap;
	*areap = new_area;
      }
      area = *areap;
    }
  }
  if (AREA_REMAINING(area) < len_in_bytes)

    s48_gc_error("out of memory in s48_allocate_weakAgc(%d).", len_in_bytes);

  result = area->frontier;
  area->frontier += S48_BYTES_TO_A_UNITS(len_in_bytes);
  return (result);
}
