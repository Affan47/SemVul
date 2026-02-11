VertexAttrib4f_nopos(GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w)
{
   GET_CURRENT_CONTEXT(ctx);
   if (index < MAX_VERTEX_GENERIC_ATTRIBS)
      ATTR(VBO_ATTRIB_GENERIC0 + index, 4, GL_FLOAT, x, y, z, w);
   else
      ERROR(GL_INVALID_VALUE);
}
