read_leb128 (unsigned char *data, unsigned int *length_return, int sign)
{
  unsigned long int result = 0;
  unsigned int num_read = 0;
  unsigned int shift = 0;
  unsigned char byte;

  do
    {
      byte = *data++;
      num_read++;

      result |= ((unsigned long int) (byte & 0x7f)) << shift;

      shift += 7;

    }
  while (byte & 0x80);

  if (length_return != NULL)
    *length_return = num_read;

  if (sign && (shift < 8 * sizeof (result)) && (byte & 0x40))
    result |= -1L << shift;

  return result;
}
