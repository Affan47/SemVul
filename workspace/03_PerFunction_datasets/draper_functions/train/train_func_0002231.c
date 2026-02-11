Scale(double *p1, double *p2, int vtkNotUsed(X), int Y)
{

  double v[3];
  v[0] = p2[0] - p1[0];
  v[1] = p2[1] - p1[1];
  v[2] = p2[2] - p1[2];

  double center[3] = {0.0,0.0,0.0};
  double avgdist = 0.0;
  double *prevctr = this->HandleGeometry[0]->GetCenter();
  double *ctr;

  center[0] += prevctr[0];
  center[1] += prevctr[1];
  center[2] += prevctr[2];

  int i;
  for ( i = 1; i < this->NumberOfHandles; ++i )
    {
    ctr = this->HandleGeometry[i]->GetCenter();
    center[0] += ctr[0];
    center[1] += ctr[1];
    center[2] += ctr[2];
    avgdist += sqrt(vtkMath::Distance2BetweenPoints(ctr,prevctr));
    prevctr = ctr;
    }

  avgdist /= this->NumberOfHandles;

  center[0] /= this->NumberOfHandles;
  center[1] /= this->NumberOfHandles;
  center[2] /= this->NumberOfHandles;


  double sf = vtkMath::Norm(v) / avgdist;
  if ( Y > this->LastEventPosition[1] )
    {
    sf = 1.0 + sf;
    }
  else
    {
    sf = 1.0 - sf;
    }


  double newCtr[3];
  for ( i = 0; i < this->NumberOfHandles; ++i )
    {
    ctr = this->HandleGeometry[i]->GetCenter();
    for ( int j = 0; j < 3; ++j )
      {
      newCtr[j] = sf * (ctr[j] - center[j]) + center[j];
      }
    this->HandleGeometry[i]->SetCenter(newCtr);
    this->HandleGeometry[i]->Update();
    }
}
