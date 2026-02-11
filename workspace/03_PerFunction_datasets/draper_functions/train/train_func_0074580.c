print_key_times (gnutls_buffer_st * str, gnutls_openpgp_crt_t cert, int idx)
{
  time_t tim;

  adds (str, _("\tTime stamps:\n"));

  if (idx == -1)
    tim = gnutls_openpgp_crt_get_creation_time (cert);
  else
    tim = gnutls_openpgp_crt_get_subkey_creation_time (cert, idx);

  {
    char s[42];
    size_t max = sizeof (s);
    struct tm t;

    if (gmtime_r (&tim, &t) == NULL)
      addf (str, "error: gmtime_r (%ld)\n", (unsigned long) tim);
    else if (strftime (s, max, "%a %b %d %H:%M:%S UTC %Y", &t) == 0)
      addf (str, "error: strftime (%ld)\n", (unsigned long) tim);
    else
      addf (str, _("\t\tCreation: %s\n"), s);
  }

  if (idx == -1)
    tim = gnutls_openpgp_crt_get_expiration_time (cert);
  else
    tim = gnutls_openpgp_crt_get_subkey_expiration_time (cert, idx);
  {
    char s[42];
    size_t max = sizeof (s);
    struct tm t;

    if (tim == 0)
      {
        adds (str, _("\t\tExpiration: Never\n"));
      }
    else
      {
        if (gmtime_r (&tim, &t) == NULL)
          addf (str, "error: gmtime_r (%ld)\n", (unsigned long) tim);
        else if (strftime (s, max, "%a %b %d %H:%M:%S UTC %Y", &t) == 0)
          addf (str, "error: strftime (%ld)\n", (unsigned long) tim);
        else
          addf (str, _("\t\tExpiration: %s\n"), s);
      }
  }
}
