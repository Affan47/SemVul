unpack_R_UINT8(const void *src, GLfloat dst[][4], GLuint n)
{
   const GLubyte *s = (const GLubyte *) src;
   GLuint i;
   for (i = 0; i < n; i++) {
      dst[i][RCOMP] = (GLfloat) s[i];
      dst[i][GCOMP] = 0.0;
      dst[i][BCOMP] = 0.0;
      dst[i][ACOMP] = 1.0;
   }
}
