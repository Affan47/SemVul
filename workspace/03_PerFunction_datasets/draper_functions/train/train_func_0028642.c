convertFrom(const imageStruct *from, GLenum to_format) {
  if (!from || !this || !from->data) {
    error("GEM: Someone sent a bogus pointer to convert");
    return;
  }
  xsize=from->xsize;
  ysize=from->ysize;

  if(to_format>0)
    setCsizeByFormat(to_format);
  else setCsizeByFormat();

  upsidedown=from->upsidedown;

  switch (from->format){
  case GL_RGBA:
    fromRGBA(from->data);
    break;
  case GL_RGB:
    fromRGB(from->data);
    break;
  case GL_BGR_EXT:
    fromBGR(from->data);
    break;
  case GL_BGRA_EXT:
    fromBGRA(from->data);
    break;
  case GL_LUMINANCE:
    fromGray(from->data);
    break;
  case GL_YCBCR_422_GEM:
    fromUYVY(from->data);
    break;
  }
}
