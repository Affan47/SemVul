encode_rgb_entries(ByteStream &bs) const
{
  const int palettesize = palette.size();
  {
    for (int c=0; c<palettesize; c++)
    {
      unsigned char p[3];
      p[2] = palette[c].p[0];
      p[1] = palette[c].p[1];
      p[0] = palette[c].p[2];
      bs.writall((const void*)p, 3);
    }
  }
}
