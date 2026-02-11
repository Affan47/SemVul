unpack_L8(const void *src, GLfloat dst[][4], GLuint n)
{
   const GLubyte *s = ((const GLubyte *) src);
   GLuint i;
   for (i = 0; i < n; i++) {
      dst[i][RCOMP] =
      dst[i][GCOMP] =
      dst[i][BCOMP] = UBYTE_TO_FLOAT(s[i]);
      dst[i][ACOMP] = 1.0F;
   }
}
