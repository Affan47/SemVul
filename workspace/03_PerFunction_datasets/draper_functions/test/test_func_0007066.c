ClipBox0D(vtkGenericCell *cell,
                                  vtkIncrementalPointLocator *locator,
                                  vtkCellArray *verts,
                                  vtkPointData *inPD,
                                  vtkPointData *outPD,
                                  vtkCellData *inCD,
                                  vtkIdType cellId,
                                  vtkCellData *outCD)
{
  vtkIdType     cellType   = cell->GetCellType();
  vtkIdList    *cellIds    = cell->GetPointIds();
  vtkCellArray *arrayvert  = vtkCellArray::New();
  vtkPoints    *cellPts    = cell->GetPoints();
  vtkIdType     npts       = cellPts->GetNumberOfPoints();
  vtkIdType     cellptId[VTK_CELL_SIZE];
  vtkIdType     iid;
  vtkIdType    *v_id = NULL;
  vtkIdType     ptId;
  vtkIdType     ptsvert = 1;

  int i;

  double v[3];

  for (i = 0; i < npts; i++)
    {
    cellptId[i] = cellIds->GetId(i);
    }


  this->CellGrid(cellType, npts, cellptId, arrayvert);

  unsigned int totalnewvert = arrayvert->GetNumberOfCells();
  for (unsigned int idlinenew = 0; idlinenew < totalnewvert; idlinenew++)
    {
    arrayvert->GetNextCell(ptsvert, v_id);


    cellPts->GetPoint(v_id[0], v);
    if (   (v[0] >= this->BoundBoxClip[0][0])
        && (v[0] <= this->BoundBoxClip[0][1])
        && (v[1] >= this->BoundBoxClip[1][0])
        && (v[1] <= this->BoundBoxClip[1][1])
        && (v[2] >= this->BoundBoxClip[2][0])
        && (v[2] <= this->BoundBoxClip[2][1]) )
      {

      ptId = cellIds->GetId(v_id[0]);
      if (locator->InsertUniquePoint(v, iid))
        {
        outPD->CopyData(inPD, ptId, iid);
        }

      int newCellId = verts->InsertNextCell(1, &iid);
      outCD->CopyData(inCD, cellId, newCellId);
      }
    }
  arrayvert->Delete();
}
