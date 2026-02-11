__getauxval (unsigned long int type)
{
  ElfW(auxv_t) *p;

#ifdef AT_HWCAP
  if (type == AT_HWCAP)
    return GLRO(dl_hwcap);
#endif

#ifdef AT_HWCAP2
  if (type == AT_HWCAP2)
    return GLRO(dl_hwcap2);
#endif

  for (p = GLRO(dl_auxv); p->a_type != AT_NULL; p++)
    if (p->a_type == type)
      return p->a_un.a_val;

  __set_errno (ENOENT);
  return 0;
}
