FindAndGetCell(double x[3],
                                      vtkCell *vtkNotUsed(cell),
                                      vtkIdType vtkNotUsed(cellId),
                                      double tol2, int& subId,
                                      double pcoords[3], double *weights)
{
  vtkIdType cellId = this->FindCell(x, 0, 0, tol2, subId, pcoords, 0);

  if (cellId < 0)
    {
    return NULL;
    }

  vtkCell *cell = this->GetCell(cellId);
  cell->InterpolateFunctions(pcoords, weights);

  return cell;
}
