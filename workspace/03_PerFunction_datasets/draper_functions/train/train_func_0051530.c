locate_index (FttVector * p, LocateArray * a, gint i[FTT_DIMENSION])
{
  gint c;
  for (c = 0; c < FTT_DIMENSION; c++)
    i[c] = floor (((&p->x)[c] - a->min[c])/a->h);
}
