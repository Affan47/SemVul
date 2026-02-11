rs_dotProd(const double *u, const double *v, int dim) const
{
  double result = 0;
  for (int i = 0; i < dim; ++i){
    result += u[i] * v[i];
  }
  return(result);
}
