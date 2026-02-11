Reset()
{
  this->SetName(0);
  this->SetDataType(VTK_VOID);
  this->SetImageMin(0);
  this->SetImageMax(0);
  this->AttributeValues->Clear();
  this->AttributeNames->Clear();
  this->VariableNames->Reset();
  this->DimensionNames->Reset();
  this->DimensionLengths->Reset();
  if (this->StringStore)
    {
    this->StringStore->Reset();
    }
  this->NumberOfImageMinMaxDimensions = 0;


  vtkStringArray *tmparray = vtkStringArray::New();
  tmparray->SetName("");
  this->AttributeNames->AddArray(tmparray);
  tmparray->Delete();
}
