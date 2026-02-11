IsValidSplit(int index)
{
  vtkIdType fedges[2];
  int i, sign;
  vtkIdType nverts=this->V->MaxId+1, j;
  double *x, val, sPt[3], v21[3], sN[3];
  vtkIdType l1[VTK_MAX_TRIS_PER_VERTEX], l2[VTK_MAX_TRIS_PER_VERTEX];
  vtkIdType n1, n2;


  fedges[0] = index;
  for ( j=0; j < (nverts-3); j++ )
    {
    fedges[1] = (index + 2 + j) % nverts;
    this->SplitLoop (fedges, n1, l1, n2, l2);


    for (i=0; i<3; i++)
      {
      sPt[i] = this->V->Array[fedges[0]].x[i];
      v21[i] = this->V->Array[fedges[1]].x[i] - sPt[i];
      }

    vtkMath::Cross (v21,this->Normal,sN);
    if ( vtkMath::Normalize(sN) == 0.0 )
      {
      return 0;
      }

    for (sign=0, i=0; i < n1; i++)
      {
      if ( !(l1[i] == fedges[0] || l1[i] == fedges[1]) )
        {
        x = this->V->Array[l1[i]].x;
        val = vtkPlane::Evaluate(sN,sPt,x);
        if ( fabs(val) < this->Tolerance )
          {
          return 0;
          }

        if ( !sign )
          {
          sign = (val > this->Tolerance ? 1 : -1);
          }
        else if ( sign != (val > 0 ? 1 : -1) )
          {
          return 0;
          }
        }
      }

    sign *= -1;
    for (i=0; i < n2; i++)
      {
      if ( !(l2[i] == fedges[0] || l2[i] == fedges[1]) )
        {
        x = this->V->Array[l2[i]].x;
        val = vtkPlane::Evaluate(sN,sPt,x);
        if ( fabs(val) < this->Tolerance )
          {
          return 0;
          }
        if ( !sign )
          {
          sign = (val > this->Tolerance ? 1 : -1);
          }
        else if ( sign != (val > 0 ? 1 : -1) )
          {
          return 0;
          }
        }
      }
    }
  return 1;
}
