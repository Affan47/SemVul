sasl_cram_md5_start(struct sasl_state* ss,
			const str* response, str* challenge)
{
  struct timeval tv;
  const char* hostname;

  if (response)
    return SASL_RESP_NOTALLOWED;
  ss->response = response1;
  if ((hostname = cvm_client_ucspi_domain()) == 0)
    hostname = "unknown";
  if (gettimeofday(&tv, 0) == -1 ||
      !str_copys(&ss->init, "<") ||
      !str_cati(&ss->init, getpid()) ||
      !str_catc(&ss->init, '.') ||
      !str_catu(&ss->init, tv.tv_sec) ||
      !str_catc(&ss->init, '.') ||
      !str_catuw(&ss->init, tv.tv_usec, 6, '0') ||
      !str_catc(&ss->init, '@') ||
      !str_cats(&ss->init, hostname) ||
      !str_catc(&ss->init, '>') ||
      !str_copy(challenge, &ss->init))
    return SASL_TEMP_FAIL;
  return SASL_CHALLENGE;
}
