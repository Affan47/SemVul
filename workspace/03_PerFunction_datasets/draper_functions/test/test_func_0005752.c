SetQuadratureWeights(const double *W)
{
  if ((this->NumberOfQuadraturePoints<=0)
      || (this->NumberOfNodes<=0)
      || (this->QuadratureWeights==0))
    {
    return;
    }

  for (int i=0; i<this->NumberOfQuadraturePoints; ++i)
    {
    this->QuadratureWeights[i]=W[i];
    }
}
