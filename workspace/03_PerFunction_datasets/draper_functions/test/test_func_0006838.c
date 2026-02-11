UpdateTriangles(vtkIdType ptId)
{
  unsigned short ncells;
  vtkIdType *cells, npts, *pts;

  this->Mesh->GetPointCells(ptId,ncells,cells);
  for (unsigned short i=0; i<ncells; i++)
    {
    this->Mesh->GetCellPoints(cells[i], npts, pts);
    this->UpdateTriangle(cells[i], (*this->PointInfo)[pts[0]],
                         (*this->PointInfo)[pts[1]], (*this->PointInfo)[pts[2]]);
    }
}
