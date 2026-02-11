gst_opengl_glMap1v (GLenum target, GLdouble u1, GLdouble u2, GLint stride,
		    GLint order, OOP pointsOOP)
{
  int npoints, size;
  GLfloat *points, *p;

  size = gst_opengl_glMap_size (target);
  if (!size)
    return GL_INVALID_ENUM;

  npoints = (order - 1) * stride + size;
  points = (GLfloat *) alloca (sizeof (GLfloat) * npoints);
  p = gst_opengl_oop_to_array (points, pointsOOP, npoints);
  if (!p)
    return GL_INVALID_VALUE;

  glMap1f (target, u1, u2, stride, order, p);
  return 0;
}
