ResetResliceCursor()
{
  vtkResliceCursorRepresentation *rep =
    reinterpret_cast<vtkResliceCursorRepresentation*>(this->WidgetRep);

  if (!rep->GetResliceCursor())
    {
    return;
    }


  rep->GetResliceCursor()->Reset();
  rep->InitializeReslicePlane();
}
