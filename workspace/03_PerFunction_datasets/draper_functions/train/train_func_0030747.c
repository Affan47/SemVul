printLogInfo(GLuint shader, const char* filename)
{
#if 1
  int isShader = vtkgl::IsShader(shader);
  if (isShader)
    {
    cout << "GLSL Shader." << endl;
    }
  else
    {
    cout << "Not a GLSL Shader!!!." << endl;
    return;
    }


  GLint type;
  vtkgl::GetShaderiv(shader, vtkgl::SHADER_TYPE, &type);


  if( type == static_cast<GLint>(vtkgl::VERTEX_SHADER) )
    {
    cout << "GLSL Vertex Shader." << endl;
    }
  else if( type == static_cast<GLint>(vtkgl::FRAGMENT_SHADER) )
    {
    cout << "GLSL Fragment Shader." << endl;
    }
  else
    {
    cout << "Not a GLSL Shader???" << endl;
    }

  GLint compiled = 0;
  GLsizei maxLength = 0;
  vtkgl::GetShaderiv(shader, vtkgl::COMPILE_STATUS, &compiled);
  vtkgl::GetShaderiv(shader, vtkgl::INFO_LOG_LENGTH, &maxLength);

  vtkgl::GLchar* info = new vtkgl::GLchar[maxLength];
  GLsizei charsWritten = 0;

  vtkgl::GetShaderInfoLog( shader, maxLength, &charsWritten, info );

  cout << "Compiled Status: " << compiled << endl;
  if( info )
    {
    cout << "Log message: " << filename << endl
         << static_cast<char *>(info) << endl;
    }

  GLSLprintOpenGLError();
#endif
}
