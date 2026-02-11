ComputeAbscissas(vtkPolyData* input, vtkDoubleArray* abscissasArray)
{
  int numberOfPoints = input->GetNumberOfPoints();

  abscissasArray->SetNumberOfTuples(numberOfPoints);
  abscissasArray->FillComponent(0,0.0);

  double point0[3], point1[3];
  double abscissa;
  vtkIdType id0, id1;

  int numberOfCells = input->GetNumberOfCells();
  int numberOfPointsInCell;

  for (int k=0; k<numberOfCells; k++)
    {
    vtkPolyLine* polyLine = vtkPolyLine::SafeDownCast(input->GetCell(k));

    if (!polyLine)
      {
      continue;
      }

    numberOfPointsInCell = polyLine->GetNumberOfPoints();

    abscissa = 0.0;

    id0 = polyLine->GetPointId(0);
    abscissasArray->SetValue(id0,abscissa);

    for (int i=1; i<numberOfPointsInCell; i++)
      {
      id0 = polyLine->GetPointId(i-1);
      id1 = polyLine->GetPointId(i);
      input->GetPoint(id0,point0);
      input->GetPoint(id1,point1);
      abscissa += sqrt(vtkMath::Distance2BetweenPoints(point0,point1));
      abscissasArray->SetValue(id1,abscissa);
      }
    }
}
