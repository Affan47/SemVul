OOGLmat_scale(QvSFMatrix *mat1, float xt, float yt, float zt)
{
  int x, y;

  for (x = 0; x < 4; x++)
    for (y = 0; y < 4; y++) {
      if (x == y)
	mat1->value[x][y] = 1.0;
      else
	mat1->value[x][y] = 0.0;
    }
  mat1->value[0][0] = xt; mat1->value[1][1] = yt; mat1->value[2][2] = zt;

}
