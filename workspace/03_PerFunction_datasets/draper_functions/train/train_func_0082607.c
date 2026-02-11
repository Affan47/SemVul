operator=(const vtkHyperPoint& hp)
{
  int i, j;

  for (i=0; i<3; i++)
    {
    this->X[i] = hp.X[i];
    this->P[i] = hp.P[i];
    this->W[i] = hp.W[i];
    for (j=0; j<3; j++)
      {
      this->V[j][i] = hp.V[j][i];
      }
    }
  this->CellId = hp.CellId;
  this->SubId = hp.SubId;
  this->S = hp.S;
  this->D = hp.D;

  return *this;
}
