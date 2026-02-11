_mesa_GetVertexAttribIiv(GLuint index, GLenum pname, GLint *params)
{
   GET_CURRENT_CONTEXT(ctx);

   if (pname == GL_CURRENT_VERTEX_ATTRIB_ARB) {
      const GLint *v = (const GLint *)
	 get_current_attrib(ctx, index, "glGetVertexAttribIiv");
      if (v != NULL) {
         COPY_4V(params, v);
      }
   }
   else {
      params[0] = (GLint) get_vertex_array_attrib(ctx, index, pname,
                                                  "glGetVertexAttribIiv");
   }
}
