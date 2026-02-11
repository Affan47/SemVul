my_char_weight_addr(CHARSET_INFO *cs, uint wc)
{
  uint page, ofst;
  uchar *ucal= cs->sort_order;
  uint16 **ucaw= cs->sort_order_big;

  return wc > MAX_UCA_CHAR_WITH_EXPLICIT_WEIGHT ? NULL :
         (ucaw[page= (wc >> 8)] ?
          ucaw[page] + (ofst= (wc & 0xFF)) * ucal[page] :
          NULL);
}
