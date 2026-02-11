ConvertPoints(vtkPoints* inPoints)
{
  this->ConvertedPoints->SetNumberOfComponents(3);
  this->ConvertedPoints->SetNumberOfTuples(inPoints->GetNumberOfPoints());
  switch (inPoints->GetDataType())
    {
    vtkTemplateMacro(vtkOpenGLProjectedAAHexahedraMapperConvertPoints(
                       static_cast<const VTK_TT *>(
                         inPoints->GetVoidPointer(0)),
                       inPoints->GetNumberOfPoints(),
                       this->ConvertedPoints->GetPointer(0) ) );
    }
  return this->ConvertedPoints->GetPointer(0);
}
