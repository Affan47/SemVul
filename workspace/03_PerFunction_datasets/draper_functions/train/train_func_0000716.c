TestLoadingScalar(
  unsigned int internalFormat,
  unsigned int format,
  unsigned int type,
  int textureSize[3],
  int componentSize)
{


  bool result;

  vtkgl::TexImage3D(vtkgl::PROXY_TEXTURE_3D,0,
                    static_cast<GLint>(internalFormat),
                    textureSize[0],textureSize[1],textureSize[2],0,
                    format,
                    type,0);
  GLint width;
  glGetTexLevelParameteriv(vtkgl::PROXY_TEXTURE_3D,0,GL_TEXTURE_WIDTH,
                           &width);

  result=width!=0;
  if(result)
    {


    vtkgl::TexImage3D(vtkgl::TEXTURE_3D,0,static_cast<GLint>(internalFormat),
                      textureSize[0],
                      textureSize[1],textureSize[2],0,
                      format,
                      type,0);
    GLenum errorCode=glGetError();
    result=errorCode!=GL_OUT_OF_MEMORY;
    if(result)
      {
      if(errorCode!=GL_NO_ERROR)
        {
        cout<<"after try to load the texture";
        cout<<" ERROR (x"<<hex<<errorCode<<") "<<dec;
        cout<<OpenGLErrorMessage(static_cast<unsigned int>(errorCode));
        cout<<endl;
        }

      result=textureSize[0]*textureSize[1]*textureSize[2]*componentSize
        <=static_cast<float>(this->MaxMemoryInBytes)*this->MaxMemoryFraction;
      }
    }
  return result;
}
