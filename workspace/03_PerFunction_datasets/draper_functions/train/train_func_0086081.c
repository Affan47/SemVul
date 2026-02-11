htt_regexcomp(apr_pool_t * p, const char *pattern,
                  const char **error, int *erroff) {
  htt_regex_t *preg = apr_palloc(p, sizeof *preg);

  preg->match = 0;
  preg->pattern = apr_pstrdup(p, pattern);

  preg->re_pcre = pcre_compile(pattern, 0, error, erroff, NULL);
  preg->re_erroffset = *erroff;

  if (preg->re_pcre == NULL) {
    return NULL;
  }

  pcre_fullinfo((const pcre *)preg->re_pcre, NULL, PCRE_INFO_CAPTURECOUNT, &(preg->re_nsub));

  apr_pool_cleanup_register(p, (void *) preg, htt_regex_cleanup,
                            apr_pool_cleanup_null);

  return preg;
}
