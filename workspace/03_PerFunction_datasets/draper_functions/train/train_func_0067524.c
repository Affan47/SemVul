ReversePoints(PointInfo *points,const int number_points)
{
  PointInfo
    point;

  register long
    i;

  for (i=0; i < (number_points >> 1); i++)
  {
    point=points[i];
    points[i]=points[number_points-(i+1)];
    points[number_points-(i+1)]=point;
  }
}
