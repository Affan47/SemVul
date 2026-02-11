resize(int n, int lb)
{
   REPORT
   Tracer tr("SymmetricBandMatrix::resize");
   if (lb<0) Throw(ProgramException("Undefined bandwidth"));
   lower_val = (lb<=n) ? lb : n-1;
   GeneralMatrix::resize(n,n,n*(lower_val+1));
}
