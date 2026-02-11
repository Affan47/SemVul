SetApplicationParameter(vtkXMLDataElement* elem)
{

  const char* name = elem->GetAttribute("name");
  if (!name)
    {
    vtkErrorMacro("Missing required attribute 'name' on element.");
    return;
    }


  const char* value = elem->GetAttribute("value");
  if (!value)
    {
    value = name;
    }


  if( this->HasShaderVariable(value) )
    {
    vtkShaderUniformVariable var = this->Internals->UniformVariables.find(value)->second;
    if( var.GetType() == VTK_INT )
      {
      std::vector<int> x(4,0);
      if( var.GetValue(&x[0])==1 )
        {
        this->SetUniformParameter( name,
                                   var.GetNumberOfValues(),
                                   &x[0]);
        }
      }
    else if( var.GetType() == VTK_FLOAT )
      {
      std::vector<float> x(4,0.0);
      if( var.GetValue(&x[0])==1 )
        {
        this->SetUniformParameter( name,
                                   var.GetNumberOfValues(),
                                   &x[0]);
        }
      }
    else if( var.GetType() == VTK_DOUBLE )
      {
      std::vector<double> x(4,0.0);
      if( var.GetValue(&x[0])==1 )
        {
        this->SetUniformParameter( name,
                                   var.GetNumberOfValues(),
                                   &x[0]);
        }
      }
    }
  else
    {
    vtkErrorMacro("Shader requires application variable " << name
      << " which is missing.");
    }
}
