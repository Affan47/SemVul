operator=(const vtkWeakPointerBase& r)
{
  if (this != &r)
    {
    if (this->Object != r.Object)
      {
      vtkWeakPointerBaseToObjectBaseFriendship::RemoveWeakPointer(
        this->Object, this);

      this->Object = r.Object;

      vtkWeakPointerBaseToObjectBaseFriendship::AddWeakPointer(
        this->Object, this);
      }
    }

  return *this;
}
