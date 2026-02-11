unpack_ubyte_GR88(const void *src, GLubyte dst[][4], GLuint n)
{
   const GLushort *s = ((const GLushort *) src);
   GLuint i;
   for (i = 0; i < n; i++) {
      dst[i][RCOMP] = s[i] & 0xff;
      dst[i][GCOMP] = s[i] >> 8;
      dst[i][BCOMP] = 0;
      dst[i][ACOMP] = 0xff;
   }
}
