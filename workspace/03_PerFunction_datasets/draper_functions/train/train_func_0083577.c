CreateColorValues(
  const double color1[3], const double color2[3], const double color3[3],
  unsigned char colors[3][3])
{


  const double *dcolors[3];
  dcolors[0] = color1;
  dcolors[1] = color2;
  dcolors[2] = color3;

  for (int i = 0; i < 3; i++)
    {
    for (int j = 0; j < 3; j++)
      {
      double val = dcolors[i][j];
      if (val < 0) { val = 0; }
      if (val > 1) { val = 1; }
      colors[i][j] = static_cast<unsigned char>(val*255);
      }
    }
}
