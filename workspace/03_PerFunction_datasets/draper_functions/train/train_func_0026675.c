orientation (FttVector * m, FttComponent * c)
{
  FttComponent i, j;
  for (i = 0; i < FTT_DIMENSION; i++)
    c[i] = i;
  for (i = 0; i < FTT_DIMENSION - 1; i++)
    for (j = 0; j < FTT_DIMENSION - 1 - i; j++)
      if (fabs ((&m->x)[c[j + 1]]) > fabs ((&m->x)[c[j]])) {
	FttComponent tmp = c[j];
	c[j] = c[j + 1];
	c[j + 1] = tmp;
      }
}
