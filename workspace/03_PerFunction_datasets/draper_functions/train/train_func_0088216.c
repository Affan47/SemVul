color_to_alpha (gfloat     *color,
                gfloat     *src,
                gint        offset)
{
  gint i;
  gfloat temp[4];

  temp[3] = src[offset + 3];

  for (i=0; i<3; i++)
    {
      if (color[i] < 1.e-4f)
        temp[i] = src[offset+i];
      else if (src[offset+i] > color[i])
        temp[i] = (src[offset+i] - color[i]) / (1.0f - color[i]);
      else if (src[offset+i] < color[i])
        temp[i] = (color[i] - src[offset+i]) / color[i];
      else
        temp[i] = 0.0f;
    }

  if (temp[0] > temp[1])
    {
      if (temp[0] > temp[2])
        src[offset+3] = temp[0];
      else
        src[offset+3] = temp[2];
    }
  else if (temp[1] > temp[2])
    src[offset+3] = temp[1];
  else
    src[offset+3] = temp[2];

  if (src[offset+3] < 1.e-4f)
    return;

  for (i=0; i<3; i++)
    src[offset+i] = (src[offset+i] - color[i]) / src[offset+3] + color[i];

  src[offset+3] *= temp[3];
}
