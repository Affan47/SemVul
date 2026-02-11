__cyg_profile_func_enter (void *this_fn, void *call_site)
{
  void *buf[2];

  if (! active)
    return;


  buf[0] = this_fn;
  buf[1] = call_site;

  write (fd, buf, sizeof buf);
}
