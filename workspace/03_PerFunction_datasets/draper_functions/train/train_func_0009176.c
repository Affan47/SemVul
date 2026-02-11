samplehalfcosparams(const Matrix& halfcosparamsranges)
{
  Tracer_Plus trace("samplehalfcosparams");

  int nparams = halfcosparamsranges.Nrows();


  ColumnVector halfcosparams(nparams);
  halfcosparams = 0;

  for(int i = 1; i <= nparams; i++)
    {

      halfcosparams(i) = unifrnd(1,1,halfcosparamsranges(i,1),halfcosparamsranges(i,2)).AsScalar();
    }

  halfcosparams.Release();
  return halfcosparams;
}
