inet6_opt_append (void *extbuf, socklen_t extlen, int offset, uint8_t type,
		  socklen_t len, uint8_t align, void **databufp)
{

  if (offset < sizeof (struct ip6_hbh))
    return -1;


  if (type == IP6OPT_PAD1 || type == IP6OPT_PADN)
    return -1;


  if (len > 255)
    return -1;


  if (align == 0 || align > 8 || (align & (align - 1)) != 0 || align > len)
    return -1;


  int data_offset = offset + sizeof (struct ip6_opt);
  int npad = (align - data_offset % align) & (align - 1);

  if (extbuf != NULL)
    {

      if (data_offset + npad + len > extlen)
	return -1;

      add_padding (extbuf, offset, npad);

      offset += npad;


      struct ip6_opt *opt = (struct ip6_opt *) ((uint8_t *) extbuf + offset);

      opt->ip6o_type = type;
      opt->ip6o_len = len;

      *databufp = opt + 1;
    }
  else
    offset += npad;

  return offset + sizeof (struct ip6_opt) + len;
}
