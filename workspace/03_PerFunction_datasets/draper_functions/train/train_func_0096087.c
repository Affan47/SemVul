SetMaskedOutputValue(int num, double *v)
{
  int idx;

  if (num < 1)
    {
    vtkErrorMacro("Output value must have length greater than 0");
    return;
    }
  if (num != this->MaskedOutputValueLength)
    {
    this->Modified();
    }

  if (num > this->MaskedOutputValueLength)
    {
    delete [] this->MaskedOutputValue;
    this->MaskedOutputValue = new double[num];
    this->MaskedOutputValueLength = num;
    }

  this->MaskedOutputValueLength = num;
  for (idx = 0; idx < num; ++ idx)
    {
    if (this->MaskedOutputValue[idx] != v[idx])
      {
      this->Modified();
      }
    this->MaskedOutputValue[idx] = v[idx];
    }
}
