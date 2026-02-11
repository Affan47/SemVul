Derivatives(int subId, double pcoords[3],
                             double *values, int dim, double *derivs)
{
  if(pcoords[2] > .999)
    {


    double pcoords1[3] = {.5, .5, 2.*.998-pcoords[2]};
    std::vector<double> derivs1(3*dim);
    this->Derivatives(subId, pcoords1, values, dim, &(derivs1[0]));
    double pcoords2[3] = {.5, .5, .998};
    std::vector<double> derivs2(3*dim);
    this->Derivatives(subId, pcoords2, values, dim, &(derivs2[0]));
    for(int i=0;i<dim*3;i++)
      {
      derivs[i] = 2.*derivs2[i] - derivs1[i];
      }
    return;
    }

  double functionDerivs[15], sum[3], value;
  int i, j, k;
  double *jI[3], j0[3], j1[3], j2[3];

  jI[0] = j0; jI[1] = j1; jI[2] = j2;
  this->JacobianInverse(pcoords, jI, functionDerivs);


  for (k=0; k < dim; k++)
    {
    sum[0] = sum[1] = sum[2] = 0.0;
    for ( i=0; i < 5; i++)
      {
      value = values[dim*i + k];
      sum[0] += functionDerivs[i] * value;
      sum[1] += functionDerivs[5 + i] * value;
      sum[2] += functionDerivs[10 + i] * value;
      }

    for (j=0; j < 3; j++)
      {
      derivs[3*k + j] = sum[0]*jI[j][0] + sum[1]*jI[j][1] + sum[2]*jI[j][2];
      }
    }
}
