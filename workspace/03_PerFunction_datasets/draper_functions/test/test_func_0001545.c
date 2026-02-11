directory_get_from_hs_dir(const char *desc_id, const rend_data_t *rend_query)
{
  smartlist_t *responsible_dirs = smartlist_new();
  routerstatus_t *hs_dir;
  char desc_id_base32[REND_DESC_ID_V2_LEN_BASE32 + 1];
  time_t now = time(NULL);
  char descriptor_cookie_base64[3*REND_DESC_COOKIE_LEN_BASE64];
  int tor2web_mode = get_options()->Tor2webMode;
  tor_assert(desc_id);
  tor_assert(rend_query);


  hid_serv_get_responsible_directories(responsible_dirs, desc_id);

  base32_encode(desc_id_base32, sizeof(desc_id_base32),
                desc_id, DIGEST_LEN);


  directory_clean_last_hid_serv_requests(now);

  SMARTLIST_FOREACH(responsible_dirs, routerstatus_t *, dir, {
      time_t last = lookup_last_hid_serv_request(
                            dir, desc_id_base32, rend_query, 0, 0);
      const node_t *node = node_get_by_id(dir->identity_digest);
      if (last + REND_HID_SERV_DIR_REQUERY_PERIOD >= now ||
          !node || !node_has_descriptor(node))
      SMARTLIST_DEL_CURRENT(responsible_dirs, dir);
  });

  hs_dir = smartlist_choose(responsible_dirs);
  smartlist_free(responsible_dirs);
  if (!hs_dir) {
    log_info(LD_REND, "Could not pick one of the responsible hidden "
                      "service directories, because we requested them all "
                      "recently without success.");
    return 0;
  }


  lookup_last_hid_serv_request(hs_dir, desc_id_base32, rend_query, now, 1);


  if (rend_query->auth_type != REND_NO_AUTH) {
    if (base64_encode(descriptor_cookie_base64,
                      sizeof(descriptor_cookie_base64),
                      rend_query->descriptor_cookie, REND_DESC_COOKIE_LEN)<0) {
      log_warn(LD_BUG, "Could not base64-encode descriptor cookie.");
      return 0;
    }

    descriptor_cookie_base64[strlen(descriptor_cookie_base64)-3] = '\0';
  } else {
    strlcpy(descriptor_cookie_base64, "(none)",
            sizeof(descriptor_cookie_base64));
  }


  directory_initiate_command_routerstatus_rend(hs_dir,
                                          DIR_PURPOSE_FETCH_RENDDESC_V2,
                                          ROUTER_PURPOSE_GENERAL,
                                          !tor2web_mode, desc_id_base32,
                                          NULL, 0, 0,
                                          rend_query);
  log_info(LD_REND, "Sending fetch request for v2 descriptor for "
                    "service '%s' with descriptor ID '%s', auth type %d, "
                    "and descriptor cookie '%s' to hidden service "
                    "directory %s",
           rend_query->onion_address, desc_id_base32,
           rend_query->auth_type,
           (rend_query->auth_type == REND_NO_AUTH ? "[none]" :
            escaped_safe_str_client(descriptor_cookie_base64)),
           routerstatus_describe(hs_dir));
  return 1;
}
