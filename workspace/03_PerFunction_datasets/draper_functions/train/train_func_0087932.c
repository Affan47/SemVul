count_vec_size (struct summary *summary, unsigned char const *tail_hits)
{
  struct summary **kids;
  unsigned int hits = (summary->sum_hits ? *summary->sum_hits : *tail_hits);

  kids = summary->sum_kids;
  if (*kids == NULL)
    {
      static char bits_per_nybble[] = { 0,1,1,2,1,2,2,3,1,2,2,3,2,3,3,4 };
      return bits_per_nybble[hits & 0xf] + bits_per_nybble[hits >> 4];
    }
  else
    {
      int bit;
      int count = 0;
      --tail_hits;
      for (bit = 1; bit & 0xff; bit <<= 1, ++kids)
	if (bit & hits)
	  count += count_vec_size (*kids, tail_hits);
      return count;
    }
}
