nl_langinfo (nl_item n)
{
#if defined (DECIMAL_POINT)
  if (n == DECIMAL_POINT)
    return decimal_point;
#endif
#if defined (RADIXCHAR)
  if (n == RADIXCHAR)
    return decimal_point;
#endif
  return "";
}
