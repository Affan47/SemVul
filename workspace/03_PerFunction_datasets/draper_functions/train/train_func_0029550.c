parse24_32BppRow(const Uint8 *row,
                                           const Uint16 width,
                                           const int bpp,
                                           char *pixData) const
{


  Uint32 x;
  Uint32 pos_a = 0;
  Uint32 pos_b = 0;


  int offset = 0;
  if (bpp == 32)
    offset = 1;

  for (x = 0; x < width; x++)
  {
    Uint8 r = row[pos_a + 2];
    Uint8 g = row[pos_a + 1];
    Uint8 b = row[pos_a];

    pixData[pos_b]     = r;
    pixData[pos_b + 1] = g;
    pixData[pos_b + 2] = b;

    pos_a += 3 + offset;
    pos_b += 3;
  }
  return EC_Normal;
}
