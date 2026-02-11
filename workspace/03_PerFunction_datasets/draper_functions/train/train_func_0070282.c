RemoveAllProps()
{
  VTK_LEGACY_REPLACED_BODY(vtkViewport::RemoveAllProps, "VTK 5.0",
                           vtkViewport::RemoveAllViewProps);
  this->RemoveAllViewProps();
}
