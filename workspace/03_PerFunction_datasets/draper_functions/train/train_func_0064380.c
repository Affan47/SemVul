EvaluateFacePlane(int plane, vtkPoints *R)
{
  int i;
  double n[3], bounds[6];
  double withN[3], oppositeN[3];

  R->GetBounds(bounds);

  this->Normals->GetTuple(plane, n);


  for (i=0; i<3; i++)
    {
    if (n[i] < 0)
      {
      withN[i]     = bounds[i*2];
      oppositeN[i] = bounds[i*2 + 1];
      }
    else
      {
      withN[i]     = bounds[i*2 + 1];
      oppositeN[i] = bounds[i*2];
      }
    }


  double *p = this->Plane + (plane * 4);

  double negVal =

    vtkPlanesIntersection::EvaluatePlaneEquation(oppositeN, p);

  if (negVal > 0)
    {
    return Outside;
    }

  double posVal =

    vtkPlanesIntersection::EvaluatePlaneEquation(withN, p);

  if (posVal < 0)
    {
    return Inside;
    }

  else             return Straddle;
}
