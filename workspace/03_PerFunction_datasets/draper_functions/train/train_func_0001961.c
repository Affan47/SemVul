EvaluatePosition(double x[3], double* closestPoint,
                                      int& subId, double pcoords[3],
                                      double& minDist2, double *weights)
{
  double pc[3], dist2;
  int ignoreId, i, return_status, status;
  double tempWeights[3], activeWeights[3];
  double closest[3];

  pcoords[2] = 0.0;

  activeWeights[0] = 0.0;
  activeWeights[1] = 0.0;
  activeWeights[2] = 0.0;

  return_status = 0;
  for (minDist2=VTK_DOUBLE_MAX,i=0; i<this->Points->GetNumberOfPoints()-2; i++)
    {
    weights[i] = 0.0;
    this->Triangle->Points->SetPoint(0,this->Points->GetPoint(i));
    this->Triangle->Points->SetPoint(1,this->Points->GetPoint(i+1));
    this->Triangle->Points->SetPoint(2,this->Points->GetPoint(i+2));
    status = this->Triangle->EvaluatePosition(x,closest,ignoreId,pc,dist2,tempWeights);
    if ( status != -1 && dist2 < minDist2 )
      {
      return_status = status;
      if (closestPoint)
        {
        closestPoint[0] = closest[0];
        closestPoint[1] = closest[1];
        closestPoint[2] = closest[2];
        }
      subId = i;
      pcoords[0] = pc[0];
      pcoords[1] = pc[1];
      pcoords[2] = 1.0 - pc[0] - pc[1];
      minDist2 = dist2;
      activeWeights[0] = tempWeights[0];
      activeWeights[1] = tempWeights[1];
      activeWeights[2] = tempWeights[2];
      }
    }

  weights[i] = 0.0;
  weights[i+1] = 0.0;

  weights[subId] = activeWeights[0];
  weights[subId+1] = activeWeights[1];
  weights[subId+2] = activeWeights[2];

  return return_status;
}
