crossProduct(int dim, ...) {


  va_list ap;

  Vector **v = new Vector* [dim-1];
  int arg_no = 0;
  va_start(ap, dim);

  while (arg_no < dim-1) {
    v[arg_no++] = va_arg(ap, Vector*);
  }
  va_end(ap);

  Matrix m(dim, dim);
  for (int k=0; k<dim; k++)
    m(0, k) = 1.0;

  for (int i=0; i < dim-1; i++) {

    if (v[i]->dimension() != dim)
      throw Vector::ArithmeticException();
    for (int j=0; j < dim; j++)
      m(i+1, j) = (*v[i])[j];
  }

  Vector result(dim);
  for (int l=0; l<dim; l++)
    result[l] = m.valueAlgebraRemainder(0, l);
  return result;
}
