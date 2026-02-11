loadProblem(const CoinPackedMatrix& matrix,
				   const double* collb, const double* colub,
				   const double* obj,
				   const char* rowsen, const double* rowrhs,
				   const double* rowrng)
{
  modelPtr_->whatsChanged_ = 0;


  int numrows = matrix.getNumRows();
  const char * rowsenUse = rowsen;
  if (!rowsen) {
    char * rowsen = new char [numrows];
    for (int i=0;i<numrows;i++)
      rowsen[i]='G';
    rowsenUse = rowsen;
  }
  const double * rowrhsUse = rowrhs;
  if (!rowrhs) {
    double * rowrhs = new double [numrows];
    for (int i=0;i<numrows;i++)
      rowrhs[i]=0.0;
    rowrhsUse = rowrhs;
  }
  const double * rowrngUse = rowrng;
  if (!rowrng) {
    double * rowrng = new double [numrows];
    for (int i=0;i<numrows;i++)
      rowrng[i]=0.0;
    rowrngUse = rowrng;
  }
  double * rowlb = new double[numrows];
  double * rowub = new double[numrows];
  for (int i = numrows-1; i >= 0; --i) {
    convertSenseToBound(rowsenUse[i],rowrhsUse[i],rowrngUse[i],rowlb[i],rowub[i]);
  }
  if (rowsen!=rowsenUse)
    delete [] rowsenUse;
  if (rowrhs!=rowrhsUse)
    delete [] rowrhsUse;
  if (rowrng!=rowrngUse)
    delete [] rowrngUse;
  loadProblem(matrix, collb, colub, obj, rowlb, rowub);
  delete [] rowlb;
  delete [] rowub;
}
