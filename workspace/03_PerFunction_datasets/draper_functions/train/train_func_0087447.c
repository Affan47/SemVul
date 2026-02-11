GetIsOpaque()
{
  vtkCompositeDataSet *input = vtkCompositeDataSet::SafeDownCast(
    this->GetInputDataObject(0, 0));
  if (this->ScalarVisibility &&
    this->ColorMode == VTK_COLOR_MODE_DEFAULT && input)
    {
    vtkSmartPointer<vtkCompositeDataIterator> iter;
    iter.TakeReference(input->NewIterator());
    for (iter->InitTraversal(); !iter->IsDoneWithTraversal(); iter->GoToNextItem())
      {
      vtkPolyData *pd = vtkPolyData::SafeDownCast(iter->GetCurrentDataObject());
      if (pd)
        {
        int cellFlag;
        vtkDataArray* scalars = this->GetScalars(pd,
          this->ScalarMode, this->ArrayAccessMode, this->ArrayId,
          this->ArrayName, cellFlag);
        if (scalars && scalars->IsA("vtkUnsignedCharArray") &&
          (scalars->GetNumberOfComponents() ==  4  ||
           scalars->GetNumberOfComponents() == 2 ))
          {
          vtkUnsignedCharArray* colors =
            static_cast<vtkUnsignedCharArray*>(scalars);
          if ((colors->GetNumberOfComponents() == 4 && colors->GetValueRange(3)[0] < 255) ||
            (colors->GetNumberOfComponents() == 2 && colors->GetValueRange(1)[0] < 255))
            {


            return false;
            }
          }
        }
      }
    }
  return this->Superclass::GetIsOpaque();
}
