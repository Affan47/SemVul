makepoints(void)
{
  GLubyte *bi = (GLubyte *) m_imageStruct.data;
  int i;

  if (!m_initialized)
    points = (cPoint *) malloc(maxPoints * sizeof(cPoint));

  numPoints = maxPoints;
  if (m_imageStruct.format == GL_YCBCR_422_GEM){
    for (i = 0; i < maxPoints; i++) {
      points[i].x = rand() % m_w>>1;
      points[i].y = rand() % m_h;
      points[i].r = bi[4 * (points[i].y * (m_w>>1) + points[i].x)];
      points[i].g = bi[4 * (points[i].y * (m_w>>1) + points[i].x) + 1];
      points[i].b = bi[4 * (points[i].y * (m_w>>1) + points[i].x) + 2];
    }
  }else{
    for (i = 0; i < maxPoints; i++) {
      points[i].x = rand() % m_w;
      points[i].y = rand() % m_h;
      points[i].r = bi[4 * (points[i].y * m_w + points[i].x) + chRed];
      points[i].g = bi[4 * (points[i].y * m_w + points[i].x) + chGreen];
      points[i].b = bi[4 * (points[i].y * m_w + points[i].x) + chBlue];
    }
  }
}
