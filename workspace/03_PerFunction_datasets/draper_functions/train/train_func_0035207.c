gt_parse_uint(unsigned int *out, const char *nptr)
{
  unsigned long ulval;
  char *ep;
  gt_assert(out && nptr);
  errno = 0;
  ulval = strtoul(nptr, &ep, 10);
  if (nptr[0] == '\0' || *ep != '\0')
    return -1;
  if ((errno == ERANGE && ulval == ULONG_MAX) || (ulval > UINT_MAX)) {
    return -1;
  }
  *out = ulval;
  return 0;
}
