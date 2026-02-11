yp_unbind (const char *indomain)
{
  __libc_lock_lock (ypbindlist_lock);

  yp_unbind_locked (indomain);

  __libc_lock_unlock (ypbindlist_lock);

  return;
}
