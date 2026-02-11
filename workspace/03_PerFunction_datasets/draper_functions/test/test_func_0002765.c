unpack_ubyte_ARGB1555(const void *src, GLubyte dst[][4], GLuint n)
{
   const GLushort *s = ((const GLushort *) src);
   GLuint i;
   for (i = 0; i < n; i++) {
      dst[i][RCOMP] = EXPAND_5_8((s[i] >> 10) & 0x1f);
      dst[i][GCOMP] = EXPAND_5_8((s[i] >>  5) & 0x1f);
      dst[i][BCOMP] = EXPAND_5_8((s[i] >>  0) & 0x1f);
      dst[i][ACOMP] = EXPAND_1_8((s[i] >> 15) & 0x01);
   }
}
