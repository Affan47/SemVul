IntersectWithLine(double p1[3], double p2[3],
                                   double vtkNotUsed(tol),
                                   vtkAssemblyPath *path,
                                   vtkProp3D *prop3D,
                                   vtkAbstractMapper3D *mapper)
{
  int i;
  double center[3], t, ray[3], rayFactor;


  if ( mapper != NULL )
    {
    mapper->GetCenter(center);
    }
  else
    {
    return VTK_DOUBLE_MAX;
    }

  for (i=0; i<3; i++)
    {
    ray[i] = p2[i] - p1[i];
    }
  if (( rayFactor = vtkMath::Dot(ray,ray)) == 0.0 )
    {
    return 2.0;
    }


  t = (ray[0]*(center[0]-p1[0]) + ray[1]*(center[1]-p1[1])
       + ray[2]*(center[2]-p1[2])) / rayFactor;

  if ( t >= 0.0 && t <= 1.0 && t < this->GlobalTMin )
    {
    this->MarkPicked(path, prop3D, mapper, t, center);
    }
  return t;
}
