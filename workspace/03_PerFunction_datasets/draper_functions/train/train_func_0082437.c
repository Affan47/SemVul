imConvertMapToRGB(unsigned char* data, int count, int depth, int packed, long* palette, int palette_count)
{
  int c, i, delta;
  unsigned char r[256], g[256], b[256];
  unsigned char *r_data, *g_data, *b_data;

  unsigned char* src_data = data + count-1;
  if (packed)
  {
    r_data = data + depth*(count-1);
    g_data = r_data + 1;
    b_data = r_data + 2;
    delta = depth;
  }
  else
  {
    r_data = data +   count - 1;
    g_data = data + 2*count - 1;
    b_data = data + 3*count - 1;
    delta = 1;
  }

  for (c = 0; c < palette_count; c++)
    imColorDecode(&r[c], &g[c], &b[c], palette[c]);

  for (i = 0; i < count; i++)
  {
    int index = *src_data;
    *r_data = r[index];
    *g_data = g[index];
    *b_data = b[index];

    r_data -= delta;
    g_data -= delta;
    b_data -= delta;
    src_data--;
  }
}
