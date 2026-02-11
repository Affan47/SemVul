processDualImage(imageStruct &left, imageStruct &right){
  char *lformat, *rformat;
  switch (left.format) {
  case GL_RGBA:
  case GL_BGRA_EXT:
    lformat =(char*)"RGBA";break;
  case GL_LUMINANCE:
    lformat =(char*)"Gray";break;
  case GL_YCBCR_422_GEM:
    lformat =(char*)"YUV";break;
  default:
    lformat = new char[6];
    sprintf(lformat,"0x%04X", (unsigned int)left.format);
  }
  switch (right.format) {
  case GL_RGBA:
  case GL_BGRA_EXT:
    rformat =(char*)"RGBA";break;
  case GL_LUMINANCE:
    rformat =(char*)"Gray";break;
  case GL_YCBCR_422_GEM:
    rformat =(char*)"YUV";break;
  default:
    rformat = new char[6];
    sprintf(rformat, "0x%04X", (unsigned int)left.format);
  }

  error("no method to combine (%s) and (%s)", lformat, rformat);
}
