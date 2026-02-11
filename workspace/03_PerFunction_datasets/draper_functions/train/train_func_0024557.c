unpack_ALPHA_INT16(const void *src, GLfloat dst[][4], GLuint n)
{
   const GLshort *s = (const GLshort *) src;
   GLuint i;
   for (i = 0; i < n; i++) {
      dst[i][RCOMP] =
      dst[i][GCOMP] =
      dst[i][BCOMP] = 0.0;
      dst[i][ACOMP] = (GLfloat) s[i];
   }
}
