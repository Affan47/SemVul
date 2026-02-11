s48_area_type_size(s48_value stob) {
  Area* area;
  area = s48_memory_map_ref(S48_ADDRESS_AT_HEADER(stob));

  if (area == NULL) {
    return AREA_TYPE_SIZE_ILLEGAL;
  }

  return area->area_type_size;
}
