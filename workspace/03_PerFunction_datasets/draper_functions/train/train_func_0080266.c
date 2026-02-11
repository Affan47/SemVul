inittable_for_usertree (char* treestr)
{


  long num_comma;
  long i, j;


  countcomma (treestr, &num_comma);
  num_comma++;

  for (i = 0; i < rcategs; i++) {
    for (j = 0; j < categs; j++) {

      free (tbl[i][j]->ww);
      free (tbl[i][j]->zz);
      free (tbl[i][j]->wwzz);
      free (tbl[i][j]->vvzz);


      tbl[i][j]->ww   = (double *) Malloc( num_comma * sizeof (double));
      tbl[i][j]->zz   = (double *) Malloc( num_comma * sizeof (double));
      tbl[i][j]->wwzz = (double *) Malloc( num_comma * sizeof (double));
      tbl[i][j]->vvzz = (double *) Malloc( num_comma * sizeof (double));
    }
  }
}
