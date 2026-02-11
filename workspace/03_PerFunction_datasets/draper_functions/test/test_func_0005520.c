got_libevent_error(void)
{
  if (++n_libevent_errors > 8) {
    log_err(LD_NET, "Too many libevent errors in one second; dying");
    return -1;
  }
  return 0;
}
