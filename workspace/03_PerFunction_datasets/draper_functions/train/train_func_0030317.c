rep_hist_circbuilding_dormant(time_t now)
{
  if (any_predicted_circuits(now))
    return 0;


  if (server_mode(get_options()) &&
      (!check_whether_orport_reachable() || !circuit_enough_testing_circs()))
    return 0;
  if (!check_whether_dirport_reachable())
    return 0;

  return 1;
}
