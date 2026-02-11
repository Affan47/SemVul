router_reload_consensus_networkstatus(void)
{
  char *filename;
  char *s;
  struct stat st;
  const or_options_t *options = get_options();
  const unsigned int flags = NSSET_FROM_CACHE | NSSET_DONT_DOWNLOAD_CERTS;
  int flav;


  for (flav = 0; flav < N_CONSENSUS_FLAVORS; ++flav) {
    char buf[128];
    const char *flavor = networkstatus_get_flavor_name(flav);
    if (flav == FLAV_NS) {
      filename = get_datadir_fname("cached-consensus");
    } else {
      tor_snprintf(buf, sizeof(buf), "cached-%s-consensus", flavor);
      filename = get_datadir_fname(buf);
    }
    s = read_file_to_str(filename, RFTS_IGNORE_MISSING, NULL);
    if (s) {
      if (networkstatus_set_current_consensus(s, flavor, flags) < -1) {
        log_warn(LD_FS, "Couldn't load consensus %s networkstatus from \"%s\"",
                 flavor, filename);
      }
      tor_free(s);
    }
    tor_free(filename);

    if (flav == FLAV_NS) {
      filename = get_datadir_fname("unverified-consensus");
    } else {
      tor_snprintf(buf, sizeof(buf), "unverified-%s-consensus", flavor);
      filename = get_datadir_fname(buf);
    }

    s = read_file_to_str(filename, RFTS_IGNORE_MISSING, NULL);
    if (s) {
      if (networkstatus_set_current_consensus(s, flavor,
                                     flags|NSSET_WAS_WAITING_FOR_CERTS)) {
      log_info(LD_FS, "Couldn't load consensus %s networkstatus from \"%s\"",
               flavor, filename);
    }
      tor_free(s);
    }
    tor_free(filename);
  }

  if (!current_consensus ||
      (stat(options->FallbackNetworkstatusFile, &st)==0 &&
       st.st_mtime > current_consensus->valid_after)) {
    s = read_file_to_str(options->FallbackNetworkstatusFile,
                         RFTS_IGNORE_MISSING, NULL);
    if (s) {
      if (networkstatus_set_current_consensus(s, "ns",
                                              flags|NSSET_ACCEPT_OBSOLETE)) {
        log_info(LD_FS, "Couldn't load consensus networkstatus from \"%s\"",
                 options->FallbackNetworkstatusFile);
      } else {
        log_notice(LD_FS,
                   "Loaded fallback consensus networkstatus from \"%s\"",
                   options->FallbackNetworkstatusFile);
      }
      tor_free(s);
    }
  }

  if (!current_consensus) {
    if (!named_server_map)
      named_server_map = strmap_new();
    if (!unnamed_server_map)
      unnamed_server_map = strmap_new();
  }

  update_certificate_downloads(time(NULL));

  routers_update_all_from_networkstatus(time(NULL), 3);
  update_microdescs_from_networkstatus(time(NULL));

  return 0;
}
