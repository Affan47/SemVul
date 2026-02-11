do_hup(void)
{
  const or_options_t *options = get_options();

#ifdef USE_DMALLOC
  dmalloc_log_stats();
  dmalloc_log_changed(0, 1, 0, 0);
#endif

  log_notice(LD_GENERAL,"Received reload signal (hup). Reloading config and "
             "resetting internal state.");
  if (accounting_is_enabled(options))
    accounting_record_bandwidth_usage(time(NULL), get_or_state());

  router_reset_warnings();
  routerlist_reset_warnings();

  if (options->ReloadTorrcOnSIGHUP) {

    if (options_init_from_torrc(0, NULL) < 0) {
      log_err(LD_CONFIG,"Reading config failed--see warnings above. "
              "For usage, try -h.");
      return -1;
    }
    options = get_options();
  } else {
    log_notice(LD_GENERAL, "Not reloading config file: the controller told "
               "us not to.");
  }
  if (authdir_mode_handles_descs(options, -1)) {

    if (dirserv_load_fingerprint_file() < 0) {

      log_info(LD_GENERAL, "Error reloading fingerprints. "
               "Continuing with old list.");
    }
  }


  circuit_expire_all_dirty_circs();


  router_reset_status_download_failures();
  router_reset_descriptor_download_failures();
  if (!options->DisableNetwork)
    update_networkstatus_downloads(time(NULL));


  if (server_mode(options)) {


    cpuworkers_rotate();
    dns_reset();
  }
  return 0;
}
