initiate_descriptor_downloads(const routerstatus_t *source,
                              int purpose,
                              smartlist_t *digests,
                              int lo, int hi, int pds_flags)
{
  int i, n = hi-lo;
  char *resource, *cp;
  size_t r_len;

  int digest_len = DIGEST_LEN, enc_digest_len = HEX_DIGEST_LEN;
  char sep = '+';
  int b64_256 = 0;

  if (purpose == DIR_PURPOSE_FETCH_MICRODESC) {


    digest_len = DIGEST256_LEN;
    enc_digest_len = BASE64_DIGEST256_LEN;
    sep = '-';
    b64_256 = 1;
  }

  if (n <= 0)
    return;
  if (lo < 0)
    lo = 0;
  if (hi > smartlist_len(digests))
    hi = smartlist_len(digests);

  r_len = 8 + (enc_digest_len+1)*n;
  cp = resource = tor_malloc(r_len);
  memcpy(cp, "d/", 2);
  cp += 2;
  for (i = lo; i < hi; ++i) {
    if (b64_256) {
      digest256_to_base64(cp, smartlist_get(digests, i));
    } else {
      base16_encode(cp, r_len-(cp-resource),
                    smartlist_get(digests,i), digest_len);
    }
    cp += enc_digest_len;
    *cp++ = sep;
  }
  memcpy(cp-1, ".z", 3);

  if (source) {

    directory_initiate_command_routerstatus(source, purpose,
                                            ROUTER_PURPOSE_GENERAL,
                                            0,
                                            resource, NULL, 0, 0);
  } else {
    directory_get_from_dirserver(purpose, ROUTER_PURPOSE_GENERAL, resource,
                                 pds_flags);
  }
  tor_free(resource);
}
