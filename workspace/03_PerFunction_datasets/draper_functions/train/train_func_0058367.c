ComputeNormal()
{
  vtkLocalPolyVertex *vtx=this->Head;
  double v1[3], v2[3], n[3], *anchor=vtx->x;

  this->Normal[0] = this->Normal[1] = this->Normal[2] = 0.0;
  for (vtx=vtx->next; vtx->next!=this->Head; vtx=vtx->next)
    {
    v1[0] = vtx->x[0] - anchor[0];
    v1[1] = vtx->x[1] - anchor[1];
    v1[2] = vtx->x[2] - anchor[2];
    v2[0] = vtx->next->x[0] - anchor[0];
    v2[1] = vtx->next->x[1] - anchor[1];
    v2[2] = vtx->next->x[2] - anchor[2];
    vtkMath::Cross(v1,v2,n);
    this->Normal[0] += n[0];
    this->Normal[1] += n[1];
    this->Normal[2] += n[2];
    }
  if ( vtkMath::Normalize(this->Normal) == 0.0 )
    {
    return 0;
    }
  else
    {
    return 1;
    }
}
