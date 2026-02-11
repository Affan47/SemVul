GetAxisRange(int i, double range[2])
{
  if ( i < 0 )
    {
    return;
    }

  vtkAxisRange arange = this->Ranges->at(i);
  range[0] = arange.Min;
  range[1] = arange.Max;
}
