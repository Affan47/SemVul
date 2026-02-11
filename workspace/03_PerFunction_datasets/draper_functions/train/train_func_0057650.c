LoadMaterial(vtkXMLMaterial* material)
{
  this->SetMaterialName(0);
  vtkSetObjectBodyMacro(Material, vtkXMLMaterial, material);
  if (this->Material)
    {
    this->SetMaterialName(this->Material->GetRootElement()->GetAttribute("name"));
    this->LoadProperty();
    this->LoadTextures();
    int lang = this->Material->GetShaderLanguage();
    int style=this->Material->GetShaderStyle();

    if(style==2)
      {
      if(lang==vtkXMLShader::LANGUAGE_GLSL)
        {

        this->ReadFrameworkMaterial();


        }
      else
        {
        vtkErrorMacro(<<"style 2 is only supported with GLSL. Failed to setup the shader.");
        this->SetShaderProgram(0);
        }
      }
    else
      {
      vtkShaderProgram* shader = vtkShaderProgram::CreateShaderProgram(lang);
      if (shader)
        {
        this->SetShaderProgram(shader);
        shader->Delete();
        this->ShaderProgram->SetMaterial(this->Material);
        this->ShaderProgram->ReadMaterial();
        }

      else if( (material->GetNumberOfVertexShaders() != 0) ||
               (material->GetNumberOfFragmentShaders() != 0) )
        {
        vtkErrorMacro("Failed to setup the shader.");
        this->SetShaderProgram(0);
        }
      }
    }
  else
    {
    this->SetShaderProgram(0);
    }
}
