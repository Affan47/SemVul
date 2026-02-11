ProcessInformation(vtkInformation* info)
{
  this->Internal->Mappings = 0;

  if( info->Has(DATA_ARRAY_TO_VERTEX_ATTRIBUTE()) )
    {
    vtkGenericVertexAttributeMapping* collection =
      vtkGenericVertexAttributeMapping::SafeDownCast(
      info->Get(DATA_ARRAY_TO_VERTEX_ATTRIBUTE()));
    this->Internal->Mappings = collection;
    }
}
