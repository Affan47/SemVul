fixFormat(GLenum wantFormat)
{
   m_type = GL_UNSIGNED_BYTE;

  if(wantFormat == GL_RGB_FLOAT32_ATI && !GLEW_ATI_texture_float) {
    wantFormat =  GL_RGB;
  }

  switch(wantFormat) {
  default:
    post("using default format");
  case GL_RGB:
    m_internalformat=m_format=GL_RGB;
    break;
  case  GL_RGB_FLOAT32_ATI:
    m_internalformat = GL_RGB_FLOAT32_ATI;
    m_format = GL_RGB;
    break;
  case GL_RGBA:
    m_internalformat = GL_RGBA;
    m_format = GL_RGBA;
    break;
  case GL_YUV422_GEM:
    m_format=GL_YUV422_GEM;
    m_internalformat=GL_RGB8;
    break;
  }

#ifdef __APPLE__
  switch(wantFormat) {
  case  GL_RGB_FLOAT32_ATI:
  m_format = GL_BGR;
  break;
  case GL_RGBA:
    m_format = GL_BGRA;
    break;
  case GL_YUV422_GEM:
    m_type = GL_UNSIGNED_SHORT_8_8_REV_APPLE;
    break;
  default:
    break;
  }
#endif
}
