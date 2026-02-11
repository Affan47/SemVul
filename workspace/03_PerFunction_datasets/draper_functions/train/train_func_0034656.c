determineMatrixForm(const matrix_t &matrix) throw (MatrixFormException)
{
  size_t nbe;
  int inc;
  matrix_form_t type;

  if (matrix.front().size() == 1)
    {
      inc = 1;
      nbe = 2;
      type = eLower;
    }
  else if (matrix.back().size() == 1)
    {
      inc = -1;
      nbe = matrix.front().size()-1;
      type = eUpper;
    }
  else
    throw MatrixFormException();


  matrix_t::const_iterator ir;
  for (ir = matrix.begin(), ir++; ir != matrix.end(); ir++, nbe += inc)
    if (ir->size() != nbe)
      throw MatrixFormException();

  return type;
}
