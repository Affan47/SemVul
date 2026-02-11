YCrCB_to_Grey_2xN(struct jdec_private *priv, int sx, int sy)
{
  const unsigned char *y;
  unsigned char *p;
  unsigned int i;
  int offset_to_next_row;

  p = priv->plane[0];
  y = priv->Y;
  offset_to_next_row = priv->bytes_per_row[0];

  for (i = sy; i > 0; i--) {
     memcpy(p, y, sx);
     y += 16;
     p += offset_to_next_row;
  }
}
