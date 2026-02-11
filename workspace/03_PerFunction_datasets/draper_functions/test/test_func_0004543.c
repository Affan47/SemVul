rend_encode_v2_intro_points(char **encoded, rend_service_descriptor_t *desc)
{
  size_t unenc_len;
  char *unenc = NULL;
  size_t unenc_written = 0;
  int i;
  int r = -1;

  unenc_len = smartlist_len(desc->intro_nodes) * 1000;
  unenc = tor_malloc_zero(unenc_len);
  for (i = 0; i < smartlist_len(desc->intro_nodes); i++) {
    char id_base32[REND_INTRO_POINT_ID_LEN_BASE32 + 1];
    char *onion_key = NULL;
    size_t onion_key_len;
    crypto_pk_t *intro_key;
    char *service_key = NULL;
    char *address = NULL;
    size_t service_key_len;
    int res;
    rend_intro_point_t *intro = smartlist_get(desc->intro_nodes, i);

    extend_info_t *info = intro->extend_info;

    base32_encode(id_base32, sizeof(id_base32),
                  info->identity_digest, DIGEST_LEN);

    if (crypto_pk_write_public_key_to_string(info->onion_key, &onion_key,
                                             &onion_key_len) < 0) {
      log_warn(LD_REND, "Could not write onion key.");
      goto done;
    }

    intro_key = intro->intro_key;
    if (!intro_key ||
      crypto_pk_write_public_key_to_string(intro_key, &service_key,
                                           &service_key_len) < 0) {
      log_warn(LD_REND, "Could not write intro key.");
      tor_free(onion_key);
      goto done;
    }

    address = tor_dup_addr(&info->addr);
    res = tor_snprintf(unenc + unenc_written, unenc_len - unenc_written,
                         "introduction-point %s\n"
                         "ip-address %s\n"
                         "onion-port %d\n"
                         "onion-key\n%s"
                         "service-key\n%s",
                       id_base32,
                       address,
                       info->port,
                       onion_key,
                       service_key);
    tor_free(address);
    tor_free(onion_key);
    tor_free(service_key);
    if (res < 0) {
      log_warn(LD_REND, "Not enough space for writing introduction point "
                        "string.");
      goto done;
    }

    unenc_written += res;
  }

  if (unenc_len < unenc_written + 2) {
    log_warn(LD_REND, "Not enough space for finalizing introduction point "
                      "string.");
    goto done;
  }
  unenc[unenc_written++] = '\n';
  unenc[unenc_written++] = 0;
  *encoded = unenc;
  r = 0;
 done:
  if (r<0)
    tor_free(unenc);
  return r;
}
