sortDecrElement()
{
  double * elements = new double [nElements_];
  int i;
  for (i=0;i<nElements_;i++)
    elements[i] = elements_[indices_[i]];
  CoinSort_2(elements, elements + nElements_, indices_,
    CoinFirstGreater_2<double, int>());
  delete [] elements;
}
