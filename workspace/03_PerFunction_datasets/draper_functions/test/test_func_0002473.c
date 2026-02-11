SetTuple(vtkIdType i, vtkIdType j, vtkAbstractArray* source)
{
  vtkBitArray* ba = vtkBitArray::SafeDownCast(source);
  if (!ba)
    {
    vtkWarningMacro("Input and output arrays types do not match.");
    return;
    }

  vtkIdType loci = i * this->NumberOfComponents;
  vtkIdType locj = j * ba->GetNumberOfComponents();
  for (vtkIdType cur = 0; cur < this->NumberOfComponents; cur++)
    {
    this->SetValue(loci + cur, ba->GetValue(locj + cur));
    }
  this->DataChanged();
}
