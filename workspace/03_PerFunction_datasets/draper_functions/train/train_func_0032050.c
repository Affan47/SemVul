GLSLprintOglError(const char *vtkNotUsed(file),
                             int vtkNotUsed(line))
{

  GLenum glErr;
  int    retCode = 0;

  glErr = glGetError();
  while (glErr != GL_NO_ERROR)
    {

    cout << "Error!" << endl;
    retCode = 1;
    glErr = glGetError();
    }
  return retCode;
}
