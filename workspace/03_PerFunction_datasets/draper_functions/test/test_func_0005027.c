_nss_compat_setpwent (int stayopen)
{
  enum nss_status result;

  __libc_lock_lock (lock);

  if (ni == NULL)
    init_nss_interface ();

  result = internal_setpwent (&ext_ent, stayopen, 1);

  __libc_lock_unlock (lock);

  return result;
}
