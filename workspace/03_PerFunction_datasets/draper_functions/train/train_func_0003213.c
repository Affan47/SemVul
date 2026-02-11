ddf_DDInputAppend(ddf_PolyhedraPtr *poly, ddf_MatrixPtr M,
  ddf_ErrorType *err)
{

  ddf_boolean found;
  ddf_ErrorType error;

  if ((*poly)->child!=NULL) ddf_FreeDDMemory(*poly);
  ddf_AppendMatrix2Poly(poly, M);
  (*poly)->representation=ddf_Inequality;
  found=ddf_DoubleDescription(*poly, &error);
  *err=error;
  return found;
}
