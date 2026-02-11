symbol_table_zero (GGobiData * d)
{
  gint j, k, m;

  for (j = 0; j < NGLYPHTYPES; j++)
    for (k = 0; k < NGLYPHSIZES; k++)
      for (m = 0; m < MAXNCOLORS; m++)
        d->symbol_table[j][k][m].n =
          d->symbol_table[j][k][m].nhidden =
          d->symbol_table[j][k][m].nshown = 0;
}
