get_prop_length(zword propoffset, int *size_length)
{
  zword prop_length;

  zbyte size_byte = LOBYTE(propoffset);
  if(zversion >= 4) {
    if(size_byte & b10000000) {
      *size_length = 2;
      prop_length = LOBYTE(propoffset + 1) & b00111111;
      if(prop_length == 0)
	prop_length = 64;
    } else {
      *size_length = 1;
      if(size_byte & b01000000)
	prop_length = 2;
      else
	prop_length = 1;
    }
  } else {
    prop_length = (size_byte >> 5) + 1;
    *size_length = 1;
  }
  return prop_length;
}
