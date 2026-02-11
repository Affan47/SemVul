_gcry_free (void *p)
{
  int save_errno;

  if (!p)
    return;


  save_errno = errno;
  if (free_func)
    free_func (p);
  else
    _gcry_private_free (p);

  if (save_errno)
    gpg_err_set_errno (save_errno);
}
