rend_cache_store_v2_desc_as_dir(const char *desc)
{
  rend_service_descriptor_t *parsed;
  char desc_id[DIGEST_LEN];
  char *intro_content;
  size_t intro_size;
  size_t encoded_size;
  char desc_id_base32[REND_DESC_ID_V2_LEN_BASE32 + 1];
  int number_parsed = 0, number_stored = 0;
  const char *current_desc = desc;
  const char *next_desc;
  rend_cache_entry_t *e;
  time_t now = time(NULL);
  tor_assert(rend_cache_v2_dir);
  tor_assert(desc);
  if (!hid_serv_acting_as_directory()) {


    log_info(LD_REND, "Cannot store descs: Not acting as hs dir");
    return -2;
  }
  while (rend_parse_v2_service_descriptor(&parsed, desc_id, &intro_content,
                                          &intro_size, &encoded_size,
                                          &next_desc, current_desc) >= 0) {
    number_parsed++;

    tor_free(intro_content);

    base32_encode(desc_id_base32, sizeof(desc_id_base32),
                  desc_id, DIGEST_LEN);


    if (!hid_serv_responsible_for_desc_id(desc_id)) {
      log_info(LD_REND, "Service descriptor with desc ID %s is not in "
                        "interval that we are responsible for.",
               safe_str_client(desc_id_base32));
      goto skip;
    }

    if (parsed->timestamp < now - REND_CACHE_MAX_AGE-REND_CACHE_MAX_SKEW) {
      log_info(LD_REND, "Service descriptor with desc ID %s is too old.",
               safe_str(desc_id_base32));
      goto skip;
    }

    if (parsed->timestamp > now + REND_CACHE_MAX_SKEW) {
      log_info(LD_REND, "Service descriptor with desc ID %s is too far in the "
                        "future.",
               safe_str(desc_id_base32));
      goto skip;
    }

    e = digestmap_get(rend_cache_v2_dir, desc_id);
    if (e && e->parsed->timestamp > parsed->timestamp) {
      log_info(LD_REND, "We already have a newer service descriptor with the "
                        "same desc ID %s and version.",
               safe_str(desc_id_base32));
      goto skip;
    }

    if (e && !strcmp(desc, e->desc)) {
      log_info(LD_REND, "We already have this service descriptor with desc "
                        "ID %s.", safe_str(desc_id_base32));
      e->received = time(NULL);
      goto skip;
    }

    if (!e) {
      e = tor_malloc_zero(sizeof(rend_cache_entry_t));
      digestmap_set(rend_cache_v2_dir, desc_id, e);
    } else {
      rend_service_descriptor_free(e->parsed);
      tor_free(e->desc);
    }
    e->received = time(NULL);
    e->parsed = parsed;
    e->desc = tor_strndup(current_desc, encoded_size);
    e->len = encoded_size;
    log_info(LD_REND, "Successfully stored service descriptor with desc ID "
                      "'%s' and len %d.",
             safe_str(desc_id_base32), (int)encoded_size);
    number_stored++;
    goto advance;
  skip:
    rend_service_descriptor_free(parsed);
  advance:

    current_desc = next_desc;

    if (!current_desc ||
        strcmpstart(current_desc, "rendezvous-service-descriptor "))
      break;
  }
  if (!number_parsed) {
    log_info(LD_REND, "Could not parse any descriptor.");
    return -1;
  }
  log_info(LD_REND, "Parsed %d and added %d descriptor%s.",
           number_parsed, number_stored, number_stored != 1 ? "s" : "");
  return number_stored;
}
