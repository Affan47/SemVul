ExtractMetadata(vtkDataSet *input)
{
  vtkModelMetadata *extractedMD = NULL;
  int numCells = static_cast<int>(this->CellList->IdTypeSet.size());

  if (vtkModelMetadata::HasMetadata(input))
    {
    if (numCells == input->GetNumberOfCells())
      {
      extractedMD = vtkModelMetadata::New();
      extractedMD->Unpack(input, 0);
      }
    else
      {
      vtkDataArray *c = input->GetCellData()->GetGlobalIds();
      vtkDataArray *p = input->GetPointData()->GetGlobalIds();

      if (c && p)
        {
        vtkIdTypeArray *cgids = vtkIdTypeArray::SafeDownCast(c);

        if (cgids)
          {
          vtkIdType *cids = cgids->GetPointer(0);

          vtkIdTypeArray *gids = vtkIdTypeArray::New();
          gids->SetNumberOfValues(numCells);

          int next = 0;
          std::set<vtkIdType>::iterator cellPtr;

          for (cellPtr = this->CellList->IdTypeSet.begin();
               cellPtr != this->CellList->IdTypeSet.end();
               ++cellPtr)
            {
            gids->SetValue(next++, cids[*cellPtr]);
            }

          vtkModelMetadata *mmd = vtkModelMetadata::New();
          mmd->Unpack(input, 0);

          extractedMD = mmd->ExtractModelMetadata(gids, input);

          gids->Delete();
          mmd->Delete();
          }
        else
          {
          vtkWarningMacro(<<
    "vtkExtractCells: metadata lost, GlobalElementId array is not a vtkIntArray");
          }
        }
      else
        {
        vtkWarningMacro(<<
    "vtkExtractCells: metadata lost, no GlobalElementId or GlobalNodeId array");
        }
      }
    }

  return extractedMD;
}
