sv2addr(SV *sv)
{
  if (SvPOK(sv) && SvCUR(sv) == sizeof(void *))
  {
    return *((void **) SvPVX(sv));
  }

  croak("invalid address value");

  return 0;
}
