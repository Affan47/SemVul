ne_net_read_str_alloc(NSOCK *sock, char **s, int *len)
{
  NEOERR *err;
  int l;


  err = ne_net_read_binary(sock, (UINT8 **)s, &l);
  if (err) return nerr_pass(err);

  if (*s != NULL)
  {
    (*s)[l] = '\0';
  }
  if (len != NULL) *len = l;
  return STATUS_OK;
}
