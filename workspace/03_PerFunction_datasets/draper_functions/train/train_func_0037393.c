GetHandlePosition(int handle)
{
  if ( handle < 0 || handle >= this->NumberOfHandles )
    {
    vtkErrorMacro(<<"vtkSplineWidget: handle index out of range.");
    return NULL;
    }

  return this->HandleGeometry[handle]->GetCenter();
}
