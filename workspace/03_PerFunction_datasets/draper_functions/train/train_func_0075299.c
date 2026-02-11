GetSteepestDescent(vtkPolyData* input, vtkIdType* edge, double s, vtkIdType* steepestDescentEdge, double &steepestDescentS)
{
  double descent, steepestDescent;
  double descentLength, steepestDescentLength;
  vtkIdType descentEdge[2];
  double descentS;
  vtkIdList *neighborCells;
  vtkIdType i, cellId;
  double directionFactor = 0.0;

  neighborCells = vtkIdList::New();

  input->GetCellEdgeNeighbors(-1,edge[0],edge[1],neighborCells);

  if (this->Direction==VTK_VMTK_DOWNWARD)
    {
    directionFactor = 1.0;
    }
  else if (this->Direction==VTK_VMTK_UPWARD)
    {
    directionFactor = - 1.0;
    }

  steepestDescent = - VTK_VMTK_LARGE_DOUBLE * directionFactor;
  steepestDescentLength = VTK_VMTK_LARGE_DOUBLE;
  steepestDescentEdge[0] = -1;
  steepestDescentEdge[1] = -1;
  for (i=0; i<neighborCells->GetNumberOfIds(); i++)
    {
    cellId = neighborCells->GetId(i);
    descent = this->GetSteepestDescentInCell(input,cellId,edge,s,descentEdge,descentS,descentLength);
    if (directionFactor*(descent - steepestDescent) > VTK_VMTK_DOUBLE_TOL)
      {
      steepestDescent = descent;
      steepestDescentLength = descentLength;
      steepestDescentEdge[0] = descentEdge[0];
      steepestDescentEdge[1] = descentEdge[1];
      steepestDescentS = descentS;
      }
    }

  neighborCells->Delete();

  return steepestDescent;
}
