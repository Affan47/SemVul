my_uca_scanner_init_ucs2(my_uca_scanner *scanner,
                                     CHARSET_INFO *cs __attribute__((unused)),
                                     const uchar *str, size_t length)
{
  scanner->wbeg= nochar;
  if (length)
  {
    scanner->sbeg= str;
    scanner->send= str + length - 2;
    scanner->uca_length= cs->sort_order;
    scanner->uca_weight= cs->sort_order_big;
    scanner->contractions= cs->contractions;
    return;
  }


  scanner->sbeg= (uchar*) &nochar[1];
  scanner->send= (uchar*) &nochar[0];
}
