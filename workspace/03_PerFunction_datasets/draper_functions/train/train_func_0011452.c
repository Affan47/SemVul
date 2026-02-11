AddColumn(vtkAbstractArray* arr)
{
  if (this->GetNumberOfColumns() > 0 &&
      arr->GetNumberOfTuples() != this->GetNumberOfRows())
    {
    vtkErrorMacro(<< "Column \"" << arr->GetName() << "\" must have "
      << this->GetNumberOfRows() << " rows, but has "
      << arr->GetNumberOfTuples() << ".");
    return;
    }
  this->RowData->AddArray(arr);
}
