_cupsSNMPOIDToString(const int *src,
                     char      *dst,
                     size_t    dstsize)
{
  char	*dstptr,
	*dstend;


  DEBUG_printf(("4_cupsSNMPOIDToString(src=%p, dst=%p, dstsize=" CUPS_LLFMT ")",
                src, dst, CUPS_LLCAST dstsize));


  if (!src || !dst || dstsize < 4)
    return (NULL);


  for (dstptr = dst, dstend = dstptr + dstsize - 1;
       *src >= 0 && dstptr < dstend;
       src ++, dstptr += strlen(dstptr))
    snprintf(dstptr, dstend - dstptr + 1, ".%d", *src);

  if (*src >= 0)
    return (NULL);
  else
    return (dst);
}
