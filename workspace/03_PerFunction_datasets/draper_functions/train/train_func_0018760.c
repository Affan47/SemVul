GenerateOddStencil (vtkIdType p1, vtkIdType p2,
                                                   vtkPolyData *polys,
                                                   vtkIdList *stencilIds,
                                                   double *weights)
{
  vtkIdList *cellIds = vtkIdList::New();
  vtkCell *cell;
  int i;
  vtkIdType cell0, cell1;
  vtkIdType p3=0, p4=0;

  polys->GetCellEdgeNeighbors (-1, p1, p2, cellIds);
  cell0 = cellIds->GetId(0);
  cell1 = cellIds->GetId(1);

  cell = polys->GetCell(cell0);
  for (i = 0; i < 3; i++)
    {
    if ((p3 = cell->GetPointId(i)) != p1 && cell->GetPointId(i) != p2)
      {
      break;
      }
    }
  cell = polys->GetCell(cell1);
  for (i = 0; i < 3; i++)
    {
    if ((p4 = cell->GetPointId(i)) != p1 && cell->GetPointId(i) != p2)
      {
      break;
      }
    }

  stencilIds->SetNumberOfIds (4);
  stencilIds->SetId(0, p1);
  stencilIds->SetId(1, p2);
  stencilIds->SetId(2, p3);
  stencilIds->SetId(3, p4);

  for (i = 0; i < stencilIds->GetNumberOfIds (); i++)
    {
    weights[i] = LoopWeights[i];
    }
  cellIds->Delete();
}
