my_uni_utf8_no_range(CHARSET_INFO *cs __attribute__((unused)),
                                my_wc_t wc, uchar *r)
{
  int count;

  if (wc < 0x80)
    count= 1;
  else if (wc < 0x800)
    count= 2;
  else if (wc < 0x10000)
    count= 3;
  else
    return MY_CS_ILUNI;

  switch (count)
  {

    case 3: r[2]= (uchar) (0x80 | (wc & 0x3f)); wc= wc >> 6; wc |= 0x800;
    case 2: r[1]= (uchar) (0x80 | (wc & 0x3f)); wc= wc >> 6; wc |= 0xc0;
    case 1: r[0]= (uchar) wc;
  }
  return count;
}
