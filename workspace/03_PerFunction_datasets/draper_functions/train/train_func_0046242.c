circuit_build_needed_circs(time_t now)
{
  static time_t time_to_new_circuit = 0;
  const or_options_t *options = get_options();


  connection_ap_attach_pending();


  rend_services_introduce();

  if (time_to_new_circuit < now) {
    circuit_reset_failure_count(1);
    time_to_new_circuit = now + options->NewCircuitPeriod;
    if (proxy_mode(get_options()))
      addressmap_clean(now);
    circuit_expire_old_circuits_clientside();

#if 0
    circ = circuit_get_youngest_clean_open(CIRCUIT_PURPOSE_C_GENERAL);
    if (get_options()->RunTesting &&
        circ &&
        circ->timestamp_created.tv_sec + TESTING_CIRCUIT_INTERVAL < now) {
      log_fn(LOG_INFO,"Creating a new testing circuit.");
      circuit_launch(CIRCUIT_PURPOSE_C_GENERAL, 0);
    }
#endif
  }
  if (!options->DisablePredictedCircuits)
    circuit_predict_and_launch_new();
}
