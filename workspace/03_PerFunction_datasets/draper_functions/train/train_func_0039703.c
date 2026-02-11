SetUpPointMap(int num_points)
{

  this->PointMap->SetNumberOfValues(num_points);
  for(int i=0; i<num_points; i++)
    {
    this->PointMap->SetValue(i, -1);
    }


  this->NumberOfUsedNodes = 0;


  this->ReversePointMap->SetNumberOfValues(num_points);
}
