calculate_interval_lengths(CHARSET_INFO *cs, TYPELIB *interval,
                                uint32 *max_length, uint32 *tot_length)
{
  const char **pos;
  uint *len;
  *max_length= *tot_length= 0;
  for (pos= interval->type_names, len= interval->type_lengths;
       *pos ; pos++, len++)
  {
    size_t length= cs->cset->numchars(cs, *pos, *pos + *len);
    *tot_length+= length;
    set_if_bigger(*max_length, (uint32)length);
  }
}
