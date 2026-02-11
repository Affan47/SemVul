Allocate2D(unsigned int width,unsigned int height,
                                  int numComps,int vtkType)
{
  this->Target=GL_TEXTURE_2D;


  if(this->Context==0)
    {
    vtkErrorMacro("No context specified. Cannot create texture.");
    return false;
    }
  GLenum internalFormat = this->GetInternalFormat(vtkType, numComps,
                                                  false);


  GLenum format = this->GetFormat(vtkType, numComps,false);

  GLenum type = ::vtkGetType(vtkType);

  this->Format = format;
  this->Type = type;
  this->Components = numComps;
  this->Width = width;
  this->Height = height;
  this->Depth =1;
  this->NumberOfDimensions=2;

  this->CreateTexture();
  this->Bind();
  glTexImage2D(this->Target, 0, static_cast<GLint>(internalFormat),
               static_cast<GLsizei>(width), static_cast<GLsizei>(height),
               0, format, type,0);
  this->UnBind();
  return true;
}
