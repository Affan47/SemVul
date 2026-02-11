EvaluateLocation(int& vtkNotUsed(subId), double pcoords[3],
                                   double x[3], double *weights)
{
  double u3;
  double pt0[3], pt1[3], pt2[3];
  int i;

  this->Points->GetPoint(0, pt0);
  this->Points->GetPoint(1, pt1);
  this->Points->GetPoint(2, pt2);

  u3 = 1.0 - pcoords[0] - pcoords[1];

  for (i=0; i<3; i++)
    {
    x[i] = pt0[i]*u3 + pt1[i]*pcoords[0] + pt2[i]*pcoords[1];
    }

  weights[0] = u3;
  weights[1] = pcoords[0];
  weights[2] = pcoords[1];
}
