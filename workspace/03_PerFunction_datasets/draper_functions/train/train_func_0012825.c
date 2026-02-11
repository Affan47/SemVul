lock_and_info (const __ptr_t caller, Dl_info *mem)
{
  if (caller == NULL)
    return NULL;

  Dl_info *res = _dl_addr (caller, mem, NULL, NULL) ? mem : NULL;

  __libc_lock_lock (lock);

  return res;
}
