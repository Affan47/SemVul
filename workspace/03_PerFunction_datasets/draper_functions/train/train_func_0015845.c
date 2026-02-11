SetUniformParameter(const char* name,
                                        int numValues,
                                        const float* values)
{
  if( !this->IsShader() )
    {
    return;
    }
  while (glGetError() != GL_NO_ERROR)
    {
    vtkErrorMacro(<< "Found unchecked OpenGL error.");
    }
  GLint loc = static_cast<GLint>(this->GetUniformLocation(name));
  if (loc == -1)
    {
    return;
    }
  switch(numValues)
    {
    case 1:
      vtkgl::Uniform1fv(loc, 1, values);
      break;
    case 2:
      vtkgl::Uniform2fv(loc, 1, values);
      break;
    case 3:
      vtkgl::Uniform3fv(loc, 1, values);
      break;
    case 4:
      vtkgl::Uniform4fv(loc, 1, values);
      break;
    default:
      vtkErrorMacro("Number of values not supported: " << numValues);
    }
  while (glGetError() != GL_NO_ERROR)
    {
    vtkErrorMacro(<< "OpenGL error when setting uniform variable int["
                  << numValues << "] " << name << ".\n"
                  << "Perhaps there is a type mismatch.");
    }
}
