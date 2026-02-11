_mesa_VertexAttribIFormat(GLuint attribIndex, GLint size, GLenum type,
                          GLuint relativeOffset)
{
   const GLbitfield legalTypes = (BYTE_BIT | UNSIGNED_BYTE_BIT |
                                  SHORT_BIT | UNSIGNED_SHORT_BIT |
                                  INT_BIT | UNSIGNED_INT_BIT);

   GET_CURRENT_CONTEXT(ctx);
   ASSERT_OUTSIDE_BEGIN_END(ctx);


   if (ctx->API == API_OPENGL_CORE &&
       ctx->Array.ArrayObj == ctx->Array.DefaultArrayObj) {
      _mesa_error(ctx, GL_INVALID_OPERATION,
                  "glVertexAttribIFormat(No array object bound)");
      return;
   }


   if (attribIndex >= ctx->Const.Program[MESA_SHADER_VERTEX].MaxAttribs) {
      _mesa_error(ctx, GL_INVALID_VALUE,
                  "glVertexAttribIFormat(attribindex=%u > "
                  "GL_MAX_VERTEX_ATTRIBS)",
                  attribIndex);
      return;
   }

   FLUSH_VERTICES(ctx, 0);

   update_array_format(ctx, "glVertexAttribIFormat",
                       VERT_ATTRIB_GENERIC(attribIndex),
                       legalTypes, 1, 4, size, type, GL_FALSE, GL_TRUE,
                       relativeOffset);
}
