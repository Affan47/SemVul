unpack_int_rgba_RGBA_INT16(const GLshort *src, GLuint dst[][4], GLuint n)
{
   unsigned int i;

   for (i = 0; i < n; i++) {
      dst[i][0] = src[i * 4 + 0];
      dst[i][1] = src[i * 4 + 1];
      dst[i][2] = src[i * 4 + 2];
      dst[i][3] = src[i * 4 + 3];
   }
}
