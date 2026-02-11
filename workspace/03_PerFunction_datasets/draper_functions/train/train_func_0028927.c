SetSamplerParameter(vtkActor* act, vtkRenderer*,
  vtkXMLDataElement* elem)
{
  const char* name = elem->GetAttribute("name");
  const char* value = elem->GetAttribute("value");
  if (!value)
    {
    vtkErrorMacro("Missing required attribute 'value' on element "
      "with name=" << name);
    return;
    }


  vtkTexture* texture = act->GetProperty()->GetTexture(value);

  if (!texture)
    {
    vtkErrorMacro("Property does have texture with name=" << value);
    return;
    }

  int texture_unit = act->GetProperty()->GetTextureUnit(value);
  this->SetSamplerParameter(name, texture, texture_unit);
}
