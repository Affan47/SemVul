asn1_set_packed(unsigned char **buffer,
		int           integer)
{
  if (integer > 0xfffffff)
  {
    **buffer = ((integer >> 28) & 0x7f) | 0x80;
    (*buffer) ++;
  }

  if (integer > 0x1fffff)
  {
    **buffer = ((integer >> 21) & 0x7f) | 0x80;
    (*buffer) ++;
  }

  if (integer > 0x3fff)
  {
    **buffer = ((integer >> 14) & 0x7f) | 0x80;
    (*buffer) ++;
  }

  if (integer > 0x7f)
  {
    **buffer = ((integer >> 7) & 0x7f) | 0x80;
    (*buffer) ++;
  }

  **buffer = integer & 0x7f;
  (*buffer) ++;
}
