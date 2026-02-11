JacobianInverse(double **inverse, double derivs[12])
{
  int i, j;
  double *m[3], m0[3], m1[3], m2[3];
  double x[3];


  this->InterpolationDerivs(NULL, derivs);


  m[0] = m0; m[1] = m1; m[2] = m2;
  for (i=0; i < 3; i++)
    {
    m0[i] = m1[i] = m2[i] = 0.0;
    }

  for ( j=0; j < 4; j++ )
    {
    this->Points->GetPoint(j, x);
    for ( i=0; i < 3; i++ )
      {
      m0[i] += x[i] * derivs[j];
      m1[i] += x[i] * derivs[4 + j];
      m2[i] += x[i] * derivs[8 + j];
      }
    }


  if ( vtkMath::InvertMatrix(m,inverse,3) == 0 )
    {
#define VTK_MAX_WARNS 3
    static int numWarns=0;
    if ( numWarns++ < VTK_MAX_WARNS )
      {
      vtkErrorMacro(<<"Jacobian inverse not found");
      vtkErrorMacro(<<"Matrix:" << m[0][0] << " " << m[0][1] << " " << m[0][2]
        << m[1][0] << " " << m[1][1] << " " << m[1][2]
        << m[2][0] << " " << m[2][1] << " " << m[2][2] );
      return 0;
      }
    }

  return 1;
}
