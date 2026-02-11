CoincidentExtremePointGroupTracts(vtkPolyData* input, vtkPolyData* centerlineTracts, bool first)
{
  vtkIntArray* groupIdsArray = vtkIntArray::New();
  groupIdsArray->SetName(this->GroupIdsArrayName);
  int numberOfCells = centerlineTracts->GetNumberOfCells();
  groupIdsArray->SetNumberOfComponents(1);
  groupIdsArray->SetNumberOfTuples(numberOfCells);

  int i;
  for (i=0; i<numberOfCells; i++)
    {
    groupIdsArray->SetValue(i,i);
    }


  for (i=0; i<numberOfCells; i++)
    {
    if (centerlineTracts->GetCell(i)->GetCellType() != VTK_LINE && centerlineTracts->GetCell(i)->GetCellType() != VTK_POLY_LINE)
      {
      continue;
      }

    int tractGroupId = groupIdsArray->GetValue(i);
    double point[3];
    if (first)
      {
      centerlineTracts->GetCell(i)->GetPoints()->GetPoint(0,point);
      }
    else
      {
      int numberOfCellPoints = centerlineTracts->GetCell(i)->GetNumberOfPoints();
      centerlineTracts->GetCell(i)->GetPoints()->GetPoint(numberOfCellPoints-1,point);
      }

    int j;
    for (j=i; j<numberOfCells; j++)
      {
      double currentPoint[3];
      if (first)
        {
        centerlineTracts->GetCell(j)->GetPoints()->GetPoint(0,currentPoint);
        }
      else
        {
        int numberOfCellPoints = centerlineTracts->GetCell(j)->GetNumberOfPoints();
        centerlineTracts->GetCell(j)->GetPoints()->GetPoint(numberOfCellPoints-1,currentPoint);
        }

      if (sqrt(vtkMath::Distance2BetweenPoints(point,currentPoint)) < VTK_VMTK_DOUBLE_TOL)
        {
        groupIdsArray->SetValue(j,tractGroupId);
        }
      }
    }

  centerlineTracts->GetCellData()->AddArray(groupIdsArray);

  groupIdsArray->Delete();
}
