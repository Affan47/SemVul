unpack_ABGR2101010_UINT(const void *src, GLfloat dst[][4], GLuint n)
{
   const GLuint *s = ((const GLuint *) src);
   GLuint i;
   for (i = 0; i < n; i++) {
      dst[i][RCOMP] = (GLfloat)((s[i] >>  0) & 0x3ff);
      dst[i][GCOMP] = (GLfloat)((s[i] >> 10) & 0x3ff);
      dst[i][BCOMP] = (GLfloat)((s[i] >> 20) & 0x3ff);
      dst[i][ACOMP] = (GLfloat)((s[i] >> 30) &  0x03);
   }
}
