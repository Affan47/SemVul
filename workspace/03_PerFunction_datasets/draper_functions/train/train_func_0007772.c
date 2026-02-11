cowt_callback(void *vdata, const struct city *pcity,
                          int arrival_time, int moves_left) {
  struct cowt_data *data = vdata;
  const struct unit *caravan = data->caravan;
  struct caravan_result current;

  caravan_result_init(&current, game_city_by_number(caravan->homecity),
                      pcity, arrival_time);


  get_discounted_reward(caravan, data->param, &current);
  if (caravan_result_compare(&current, data->best) > 0) {
    *data->best = current;
  }


  if (city_owner(pcity) == unit_owner(caravan)) {
    caravan_find_best_destination_withtransit(
        caravan, data->param, pcity, arrival_time, moves_left, &current);
    if (caravan_result_compare(&current, data->best) > 0) {
      *data->best = current;
    }
  }

  return FALSE;
}
