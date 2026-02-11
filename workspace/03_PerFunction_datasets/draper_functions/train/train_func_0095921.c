unpack_RGBA_INT8(const void *src, GLfloat dst[][4], GLuint n)
{
   const GLbyte *s = (const GLbyte *) src;
   GLuint i;
   for (i = 0; i < n; i++) {
      dst[i][RCOMP] = (GLfloat) s[i*4+0];
      dst[i][GCOMP] = (GLfloat) s[i*4+1];
      dst[i][BCOMP] = (GLfloat) s[i*4+2];
      dst[i][ACOMP] = (GLfloat) s[i*4+3];
   }
}
