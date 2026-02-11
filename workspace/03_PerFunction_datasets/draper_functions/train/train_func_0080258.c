AllocateDepthMap(void)
{
  magick_uint8_t
    *map;

  map = MagickAllocateArray(unsigned char *, MaxMap+1, sizeof(magick_uint8_t));
  if (map != (unsigned char *) NULL)
    {
      unsigned int
        i;

      for (i=0; i <= MaxMap; i++)
        map[i] = (magick_uint8_t) MinimumDepthForValue(i);
    }
  return map;
}
