gulp_shape_indices_compute(struct gulp_pak *gulp)
{
gint i, j, n;
gdouble a, b, c;

g_assert(gulp != NULL);

switch (gulp->cosmo_shape)
  {
  case 0:
    c = 4.0;
    break;
  default:
    c = 10.0;
    break;
  }

a = gulp->cosmo_points;
a = log((a - 2.0) / c) / log(3.0);
b = log(4.0) / log(3.0);


for (j=0 ; j<COSMO_SHAPE_INDEX_MAX ; j++)
  {
  i = nearest_int(a - j*b);

  n = nearest_int (c * pow(3.0, (gdouble) i) * pow(4.0, (gdouble) j) + 2.0);


  if (!(n - gulp->cosmo_points))
    {
    gulp->cosmo_shape_index[0] = i;
    gulp->cosmo_shape_index[1] = j;

    return(TRUE);
    }
  }
return(FALSE);
}
