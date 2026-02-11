call_internal_write_barrier(Area* maybe_area, char area_looked_up, s48_address addr,
					       s48_value stob, Area* to_area) {
  if (!area_looked_up) maybe_area = s48_memory_map_ref(addr);


  if ((maybe_area != NULL) && (maybe_area->generation_index > 0))
    s48_internal_write_barrier(maybe_area, addr, stob, to_area);
}
