ippCopyAttributes(
    ipp_t        *dst,
    ipp_t        *src,
    int          quickcopy,
    ipp_copycb_t cb,
    void         *context)
{
  ipp_attribute_t	*srcattr;


  DEBUG_printf(("ippCopyAttributes(dst=%p, src=%p, quickcopy=%d, cb=%p, context=%p)",
                dst, src, quickcopy, cb, context));


  if (!dst || !src)
    return (0);


  for (srcattr = src->attrs; srcattr; srcattr = srcattr->next)
    if (!cb || (*cb)(context, dst, srcattr))
      if (!ippCopyAttribute(dst, srcattr, quickcopy))
        return (0);

  return (1);
}
