glxewGetExtension (const char* name)
{
  GLubyte* p;
  GLubyte* end;
  GLuint len;

  if (glXGetCurrentDisplay == NULL) return GL_FALSE;
  len = _glewStrLen((const GLubyte*)name);
  p = (GLubyte*)glXGetClientString(glXGetCurrentDisplay(), GLX_EXTENSIONS);
  if (0 == p) return GL_FALSE;
  end = p + _glewStrLen(p);
  while (p < end)
  {
    GLuint n = _glewStrCLen(p, ' ');
    if (len == n && _glewStrSame((const GLubyte*)name, p, n)) return GL_TRUE;
    p += n+1;
  }
  return GL_FALSE;
}
