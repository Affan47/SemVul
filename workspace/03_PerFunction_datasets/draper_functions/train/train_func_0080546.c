verify_expiration(time_t expires_secs, int *remaining)
{
  time_t now;

  time(&now);

  if (expires_secs == (time_t) -1)
	return(-1);

  if (remaining != NULL)
	*remaining = (int) (expires_secs - now);

  if (expires_secs > now)
	return(1);

  return(0);
}
