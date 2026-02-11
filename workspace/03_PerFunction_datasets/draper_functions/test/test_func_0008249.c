translate_id(GLsizei n, GLenum type, const GLvoid * list)
{
   GLbyte *bptr;
   GLubyte *ubptr;
   GLshort *sptr;
   GLushort *usptr;
   GLint *iptr;
   GLuint *uiptr;
   GLfloat *fptr;

   switch (type) {
   case GL_BYTE:
      bptr = (GLbyte *) list;
      return (GLint) bptr[n];
   case GL_UNSIGNED_BYTE:
      ubptr = (GLubyte *) list;
      return (GLint) ubptr[n];
   case GL_SHORT:
      sptr = (GLshort *) list;
      return (GLint) sptr[n];
   case GL_UNSIGNED_SHORT:
      usptr = (GLushort *) list;
      return (GLint) usptr[n];
   case GL_INT:
      iptr = (GLint *) list;
      return iptr[n];
   case GL_UNSIGNED_INT:
      uiptr = (GLuint *) list;
      return (GLint) uiptr[n];
   case GL_FLOAT:
      fptr = (GLfloat *) list;
      return (GLint) FLOORF(fptr[n]);
   case GL_2_BYTES:
      ubptr = ((GLubyte *) list) + 2 * n;
      return (GLint) ubptr[0] * 256
           + (GLint) ubptr[1];
   case GL_3_BYTES:
      ubptr = ((GLubyte *) list) + 3 * n;
      return (GLint) ubptr[0] * 65536
           + (GLint) ubptr[1] * 256
           + (GLint) ubptr[2];
   case GL_4_BYTES:
      ubptr = ((GLubyte *) list) + 4 * n;
      return (GLint) ubptr[0] * 16777216
           + (GLint) ubptr[1] * 65536
           + (GLint) ubptr[2] * 256
           + (GLint) ubptr[3];
   default:
      return 0;
   }
}
