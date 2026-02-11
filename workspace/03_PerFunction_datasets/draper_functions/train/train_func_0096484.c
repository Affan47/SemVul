WriteCellsAppendedData(vtkCellArray* cells,
                                                     vtkDataArray* types,
                                                     vtkIdTypeArray* faces,
                                                     vtkIdTypeArray* faceOffsets,
                                                     int timestep,
                                                     OffsetsManagerGroup *cellsManager)
{
  if (cells)
    {
    this->ConvertCells(cells);
    }

  this->ConvertFaces(faces, faceOffsets);


  float progressRange[5] = {0,0,0,0,0};
  this->GetProgressRange(progressRange);
  float fractions[6];
  this->CalculateCellFractions(fractions, types?types->GetNumberOfTuples():0);


  vtkDataArray *allcells[5];
  allcells[0] = this->CellPoints;
  allcells[1] = this->CellOffsets;
  allcells[2] = types;
  allcells[3] = this->Faces->GetNumberOfTuples() ? this->Faces : 0;
  allcells[4] = this->FaceOffsets->GetNumberOfTuples() ? this->FaceOffsets : 0;

  for(int i=0; i<5; i++)
    {
    if(allcells[i])
      {

      this->SetProgressRange(progressRange, i, fractions);

      unsigned long mtime = allcells[i]->GetMTime();
      unsigned long &cellsMTime = cellsManager->GetElement(i).GetLastMTime();

      if( cellsMTime != mtime )
        {
        cellsMTime = mtime;

        this->WriteArrayAppendedData(allcells[i],
          cellsManager->GetElement(i).GetPosition(timestep),
          cellsManager->GetElement(i).GetOffsetValue(timestep));
        if (this->ErrorCode == vtkErrorCode::OutOfDiskSpaceError)
          {
          return;
          }
        }
      else
        {


        assert( timestep > 0 );
        cellsManager->GetElement(i).GetOffsetValue(timestep) =
          cellsManager->GetElement(i).GetOffsetValue(timestep-1);
        this->ForwardAppendedDataOffset(cellsManager->GetElement(i).GetPosition(timestep),
                                        cellsManager->GetElement(i).GetOffsetValue(timestep),
                                        "offset" );
        }
      }
    }
}
