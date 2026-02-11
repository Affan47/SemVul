_nss_compat_getpwent_r (struct passwd *pwd, char *buffer, size_t buflen,
			int *errnop)
{
  enum nss_status result = NSS_STATUS_SUCCESS;

  __libc_lock_lock (lock);


  if (ni == NULL)
    init_nss_interface ();

  if (ext_ent.stream == NULL)
    result = internal_setpwent (&ext_ent, 1, 1);

  if (result == NSS_STATUS_SUCCESS)
    result = internal_getpwent_r (pwd, &ext_ent, buffer, buflen, errnop);

  __libc_lock_unlock (lock);

  return result;
}
