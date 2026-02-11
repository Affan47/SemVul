IsTriangleObtuse(double point0[3], double point1[3], double point2[3])
  {
  if (IsAngleObtuse(point0,point1,point2))
    return VTK_VMTK_OBTUSE_IN_POINT;
  else if (IsAngleObtuse(point2,point0,point1) || IsAngleObtuse(point1,point2,point0))
    return VTK_VMTK_OBTUSE_NOT_IN_POINT;

  return VTK_VMTK_NON_OBTUSE;
  }
