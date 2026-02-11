unpack_Z32_FLOAT(const void *src, GLfloat dst[][4], GLuint n)
{
   const GLfloat *s = ((const GLfloat *) src);
   GLuint i;
   for (i = 0; i < n; i++) {
      dst[i][0] =
      dst[i][1] =
      dst[i][2] = s[i * 2];
      dst[i][3] = 1.0F;
   }
}
