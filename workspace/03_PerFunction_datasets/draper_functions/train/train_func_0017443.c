_gnutls_io_clear_peeked_data (gnutls_session_t session)
{
  mbuffer_st *peekdata;
  int ret, sum;

  if (session->internals.have_peeked_data == 0 || RCVLOWAT == 0)
    return 0;


  sum = 0;
  do
    {
      ret =
        _gnutls_read (session, &peekdata, RCVLOWAT - sum,
                      session->internals.pull_func);
      if (ret > 0)
        sum += ret;
      _mbuffer_xfree (&peekdata);
    }
  while (ret == GNUTLS_E_INTERRUPTED || ret == GNUTLS_E_AGAIN
         || sum < RCVLOWAT);

  if (ret < 0)
    {
      gnutls_assert ();
      return ret;
    }

  session->internals.have_peeked_data = 0;

  return 0;
}
