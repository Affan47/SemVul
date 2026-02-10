directory_info_has_arrived(time_t now, int from_cache)
{
  const or_options_t *options = get_options();

  if (!router_have_minimum_dir_info()) {
    int quiet = directory_too_idle_to_fetch_descriptors(options, now);
    log(quiet ? LOG_INFO : LOG_NOTICE, LD_DIR,
        "I learned some more directory information, but not enough to "
        "build a circuit: %s", get_dir_info_status_string());
    update_all_descriptor_downloads(now);
    return;
  } else {
    if (directory_fetches_from_authorities(options)) {
      update_all_descriptor_downloads(now);
    }


    entry_guards_compute_status(options, now);


    if (options->DownloadExtraInfo)
      update_extrainfo_downloads(now);
  }

  if (server_mode(options) && !net_is_disabled() && !from_cache &&
      (can_complete_circuit || !any_predicted_circuits(now)))
    consider_testing_reachability(1, 1);
}
