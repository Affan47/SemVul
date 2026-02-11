WriteInlinePiece(vtkIndent indent)
{

  vtkDataSet* input = this->GetInputAsDataSet();


  float progressRange[2] = {0,0};
  this->GetProgressRange(progressRange);
  int pdArrays = input->GetPointData()->GetNumberOfArrays();
  int cdArrays = input->GetCellData()->GetNumberOfArrays();
  int total = (pdArrays+cdArrays)? (pdArrays+cdArrays):1;
  float fractions[3] =
    {
      0,
      float(pdArrays)/total,
      1
    };


  this->SetProgressRange(progressRange, 0, fractions);
  this->WritePointDataInline(input->GetPointData(), indent);
  if (this->ErrorCode == vtkErrorCode::OutOfDiskSpaceError)
    {
    return;
    }


  this->SetProgressRange(progressRange, 1, fractions);
  this->WriteCellDataInline(input->GetCellData(), indent);
}
