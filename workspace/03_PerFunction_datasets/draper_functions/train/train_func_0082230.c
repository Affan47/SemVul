nerr_handle (NEOERR **err, int etype)
{
  NEOERR *walk = *err;

  while (walk != STATUS_OK && walk != INTERNAL_ERR)
  {

    if (walk->error == etype)
    {
      _err_free(*err);
      *err = STATUS_OK;
      return 1;
    }
    walk = walk->next;
  }

  if (walk == STATUS_OK && etype == STATUS_OK_INT)
    return 1;
  if (walk == STATUS_OK)
    return 0;

  if (walk == INTERNAL_ERR && etype == INTERNAL_ERR_INT)
  {
    *err = STATUS_OK;
    return 1;
  }
  if (walk == INTERNAL_ERR)
    return 0;

  return 0;
}
