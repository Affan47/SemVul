TraverseAndMark (vtkDataSet *input)
{
  vtkIdType i, j, k, cellId, numIds, ptId, numPts, numCells;
  vtkIdList *tmpWave;

  while ( (numIds=this->Wave->GetNumberOfIds()) > 0 )
    {
    for ( i=0; i < numIds; i++ )
      {
      cellId = this->Wave->GetId(i);
      if ( this->Visited[cellId] < 0 )
        {
        this->NewCellScalars->SetValue(cellId, this->RegionNumber);
        this->Visited[cellId] = this->RegionNumber;
        this->NumCellsInRegion++;
        input->GetCellPoints(cellId, this->PointIds);

        numPts = this->PointIds->GetNumberOfIds();
        for (j=0; j < numPts; j++)
          {
          if ( this->PointMap[ptId=this->PointIds->GetId(j)] < 0 )
            {
            this->PointMap[ptId] = this->PointNumber++;
            this->NewScalars->SetValue(this->PointMap[ptId],
                                       this->RegionNumber);
            }

          input->GetPointCells(ptId,this->CellIds);


          numCells = this->CellIds->GetNumberOfIds();
          for (k=0; k < numCells; k++)
            {
            cellId = this->CellIds->GetId(k);
            if ( this->InScalars )
              {
              int numScalars, ii;
              double s, range[2];

              input->GetCellPoints(cellId, this->NeighborCellPointIds);
              numScalars = this->NeighborCellPointIds->GetNumberOfIds();
              this->CellScalars->SetNumberOfComponents(this->InScalars->GetNumberOfComponents());
              this->CellScalars->SetNumberOfTuples(numScalars);
              this->InScalars->GetTuples(this->NeighborCellPointIds,
                                         this->CellScalars);
              range[0] = VTK_DOUBLE_MAX; range[1] = -VTK_DOUBLE_MAX;
              for (ii=0; ii < numScalars;  ii++)
                {
                s = this->CellScalars->GetComponent(ii,0);
                if ( s < range[0] )
                  {
                  range[0] = s;
                  }
                if ( s > range[1] )
                  {
                  range[1] = s;
                  }
                }
              if ( range[1] >= this->ScalarRange[0] &&
                   range[0] <= this->ScalarRange[1] )
                {
                this->Wave2->InsertNextId(cellId);
                }
              }
            else
              {
              this->Wave2->InsertNextId(cellId);
              }
            }
          }
        }
      }

    tmpWave = this->Wave;
    this->Wave = this->Wave2;
    this->Wave2 = tmpWave;
    tmpWave->Reset();
    }

  return;
}
