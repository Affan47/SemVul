_mesa_VertexAttribs2fvNV(GLuint index, GLsizei n, const GLfloat *v)
{
   GLint i;
   for (i = n - 1; i >= 0; i--)
      ATTRIB2NV(index + i, v[2 * i], v[2 * i + 1]);
}
