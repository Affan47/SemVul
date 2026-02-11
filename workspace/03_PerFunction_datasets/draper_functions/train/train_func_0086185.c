LoadShader()
{

  if( !this->IsShader() )
    {

    switch (this->XMLShader->GetScope())
      {
      case vtkXMLShader::SCOPE_VERTEX:
        this->Shader = vtkgl::CreateShader( vtkgl::VERTEX_SHADER );
        break;
      case vtkXMLShader::SCOPE_FRAGMENT:
        this->Shader = vtkgl::CreateShader( vtkgl::FRAGMENT_SHADER );
        break;
      }
    }
}
