cm_result_copy(struct cm_result *result,
                           const struct city *pcity, bool *workers_map)
{
  struct tile *pcenter = city_tile(pcity);


  memset(result->worker_positions, 0,
         sizeof(*result->worker_positions)
         * city_map_tiles(result->city_radius_sq));

  city_tile_iterate_index(result->city_radius_sq, pcenter, ptile, index) {
    if (workers_map == NULL) {

      struct city *pwork = tile_worked(ptile);

      result->worker_positions[index] = (NULL != pwork && pwork == pcity);
    } else {
      result->worker_positions[index] = workers_map[index];
    }
  } city_tile_iterate_index_end;


  specialist_type_iterate(spec) {
    result->specialists[spec] = pcity->specialists[spec];
  } specialist_type_iterate_end;


  get_city_surplus(pcity, result->surplus,
      &result->disorder, &result->happy);


  result->found_a_valid = TRUE;
}
