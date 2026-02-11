ComputeSurfaceTCoord(vtkDataSet *data, vtkCell *cell,
                                           const double *weights,
                                           double tcoord[3])
{
  vtkDataArray *tcoords = data->GetPointData()->GetTCoords();

  if (tcoords)
    {
    tcoord[0] = tcoord[1] = tcoord[2] = 0.0;
    double pointTCoord[3];

    int numComponents = tcoords->GetNumberOfComponents();
    vtkIdType numPoints = cell->GetNumberOfPoints();
    for (vtkIdType k = 0; k < numPoints; k++)
      {
      tcoords->GetTuple(cell->PointIds->GetId(k), pointTCoord);
      for (int i = 0; i < numComponents; i++)
        {
        tcoord[i] += pointTCoord[i]*weights[k];
        }
      }

    return 1;
    }

  return 0;
}
