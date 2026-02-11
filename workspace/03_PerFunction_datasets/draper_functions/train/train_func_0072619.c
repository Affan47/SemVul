TRIANGLE_CQS_VECTOR( double v0[3], double v1[3], double p[3], double cqs[3] )
{
  double length = sqrt(vtkMath::Distance2BetweenPoints(v0,v1));
  double a[3], b[3], c[3];
  for(int i=0;i<3;i++)
    {
    a[i] = v1[i] - v0[i];
    b[i] = p[i] - v0[i];
    }
  vtkMath::Cross( a, b, c );
  vtkMath::Cross( c , a , cqs );
  vtkMath::Normalize(cqs);
  SCALE_VEC( cqs , length / 2.0 );
}
