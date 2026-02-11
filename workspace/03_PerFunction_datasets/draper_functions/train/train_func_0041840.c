static_allocate_increase (int *range)
{
char *indices_old, *indices;
int *range_old;
int ii_old, jj_old, kk_old;
int ii, jj, kk;
int i, j, k;
int b_old, c_old;
int a, b, c;

indices_old = list.indices;
range_old = list.range;


a = range[1] - range[0] + 1;
b = range[3] - range[2] + 1;
c = range[5] - range[4] + 1;
indices = (char *) calloc (a * b * c, sizeof (char));

if (indices_old != NULL)
  {
  b_old = range_old[3] - range_old[2] + 1;
  c_old = range_old[5] - range_old[4] + 1;

  for (i = range_old[0]; i <= range_old[1]; i++)
    {
    ii_old = i - range_old[0];
    ii = i - range[0];

    for (j = range_old[2]; j <= range_old[3]; j++)
      {
      jj_old = j - range_old[2];
      jj = j - range[2];

      for (k = range_old[4]; k <= range_old[5]; k++)
        {
        kk_old = k - range_old[4];
        kk = k - range[4];

        indices[b * c * ii + c * jj + kk] =
        indices_old[b_old * c_old * ii_old + c_old * jj_old + kk_old];
        }
      }
    }

  free (indices_old);
  }

list.indices = indices;


range_old[0] = range[0];
range_old[1] = range[1];
range_old[2] = range[2];
range_old[3] = range[3];
range_old[4] = range[4];
range_old[5] = range[5];
}
