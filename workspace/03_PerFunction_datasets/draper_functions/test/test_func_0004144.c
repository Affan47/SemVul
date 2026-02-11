_mesa_unpack_polygon_stipple( const GLubyte *pattern, GLuint dest[32],
                              const struct gl_pixelstore_attrib *unpacking )
{
   GLubyte *ptrn = (GLubyte *) _mesa_unpack_bitmap(32, 32, pattern, unpacking);
   if (ptrn) {


      GLubyte *p = ptrn;
      GLint i;
      for (i = 0; i < 32; i++) {
         dest[i] = (p[0] << 24)
                 | (p[1] << 16)
                 | (p[2] <<  8)
                 | (p[3]      );
         p += 4;
      }
      free(ptrn);
   }
}
