untriplet(offset *location, int *shift_amt)
{
  unsigned triplet;
  unsigned char result;
  if(*shift_amt == END) {
    if(!testing_string)
      n_show_error(E_STRING, "attempt to read past end of string", *location);
    string_bad = TRUE;
    return 0;
  }
  triplet = HISTRWORD(*location);
  result = (triplet >> *shift_amt) & b00011111;

  *shift_amt -= 5;

  if(*shift_amt < 0) {
    *shift_amt = 10;
    *location += 2;

    if(triplet & 0x8000)
      *shift_amt = END;
  }
  return result;
}
