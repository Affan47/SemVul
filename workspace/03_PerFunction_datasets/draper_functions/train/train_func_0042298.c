MapDataArrayToMultiTextureAttribute(
  int unit,
  const char* dataArrayName,
  int field,
  int componentno)
{
  vtkGenericVertexAttributeMapping* mappings = 0;
  if( this->PainterInformation->Has(
      vtkPrimitivePainter::DATA_ARRAY_TO_VERTEX_ATTRIBUTE()) )
    {
    mappings = vtkGenericVertexAttributeMapping::SafeDownCast(
      this->PainterInformation->Get(
        vtkPolyDataPainter::DATA_ARRAY_TO_VERTEX_ATTRIBUTE()));
    }

  if (mappings==NULL)
    {
    mappings = vtkGenericVertexAttributeMapping::New();
    this->PainterInformation->Set(
      vtkPolyDataPainter::DATA_ARRAY_TO_VERTEX_ATTRIBUTE(), mappings);
    mappings->Delete();
    }

  mappings->AddMapping(
    unit, dataArrayName, field, componentno);
}
