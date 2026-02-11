DeepCopy(
  vtkStructuredVisibilityConstraint* src)
{
  memcpy(this->Dimensions, src->Dimensions, 3*sizeof(int));

  this->NumberOfIds =
    static_cast<vtkIdType>(this->Dimensions[0])*
    static_cast<vtkIdType>(this->Dimensions[1])*
    static_cast<vtkIdType>(this->Dimensions[2]);
  if(src->VisibilityById)
    {
    if (!this->VisibilityById)
      {
      this->VisibilityById = vtkUnsignedCharArray::New();
      }
    this->VisibilityById->DeepCopy(src->VisibilityById);
    }
  this->Initialized = src->Initialized;
}
