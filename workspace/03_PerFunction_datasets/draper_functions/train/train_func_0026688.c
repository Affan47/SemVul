fread_le (const char *data)
{
  unsigned int x;
  uint32_t result = 0;

  for (x = 0; x < 4; x++)
    result |= ((unsigned char) data[x]) << (x * 8);
  return result;
}
