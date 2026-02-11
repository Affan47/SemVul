unpack_ARGB4444(const void *src, GLfloat dst[][4], GLuint n)
{
   const GLushort *s = ((const GLushort *) src);
   GLuint i;
   for (i = 0; i < n; i++) {
      dst[i][RCOMP] = ((s[i] >>  8) & 0xf) * (1.0F / 15.0F);
      dst[i][GCOMP] = ((s[i] >>  4) & 0xf) * (1.0F / 15.0F);
      dst[i][BCOMP] = ((s[i]      ) & 0xf) * (1.0F / 15.0F);
      dst[i][ACOMP] = ((s[i] >> 12) & 0xf) * (1.0F / 15.0F);
   }
}
