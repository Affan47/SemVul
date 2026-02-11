ddf_CopyInput(ddf_PolyhedraPtr poly)
{
  ddf_MatrixPtr M=NULL;
  ddf_rowrange i;

  M=ddf_CreateMatrix(poly->m, poly->d);
  ddf_CopyAmatrix(M->matrix, poly->A, poly->m, poly->d);
  for (i=1; i<=poly->m; i++)
    if (poly->EqualityIndex[i]==1) set_addelem(M->linset,i);
  ddf_MatrixIntegerFilter(M);
  if (poly->representation==ddf_Generator)
    M->representation=ddf_Generator;
  else
    M->representation=ddf_Inequality;
  return M;
}
