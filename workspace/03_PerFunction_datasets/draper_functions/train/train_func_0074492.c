ProcessInformation(vtkInformation *info)
{
  this->GenericVertexAttributes = false;
  if (info->Has(DATA_ARRAY_TO_VERTEX_ATTRIBUTE()))
    {
    vtkGenericVertexAttributeMapping *mappings =
      vtkGenericVertexAttributeMapping::SafeDownCast(
      info->Get(DATA_ARRAY_TO_VERTEX_ATTRIBUTE()));
    this->GenericVertexAttributes = mappings &&
      (mappings->GetNumberOfMappings() > 0);
    this->MultiTextureAttributes = false;
    if (mappings)
      {
      for (unsigned int i = 0; i < mappings->GetNumberOfMappings(); ++i)
        {
        if (mappings->GetTextureUnit(i) >= 0)
          {
          this->MultiTextureAttributes = true;
          break;
          }
        }
      }
    }

  if (info->Has(DISABLE_SCALAR_COLOR()) &&
    info->Get(DISABLE_SCALAR_COLOR()) == 1)
    {
    this->DisableScalarColor = 1;
    }
  else
    {
    this->DisableScalarColor = 0;
    }
}
