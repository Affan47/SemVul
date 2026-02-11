unpack_ubyte_s_Z32_FLOAT_X24S8(const void *src, GLubyte *dst, GLuint n)
{
   GLuint i;
   const struct z32f_x24s8 *s = (const struct z32f_x24s8 *) src;

   for (i = 0; i < n; i++)
      dst[i] = s[i].x24s8 & 0xff;
}
