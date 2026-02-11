is_exlen_apdu (const unsigned char *apdu, size_t apdulen)
{
  if (apdulen < 7 || apdu[4])
    return 0;
  return 1;
}
