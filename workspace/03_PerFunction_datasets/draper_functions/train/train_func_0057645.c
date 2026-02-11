_save_OBE_MultiDrawElementsBaseVertex(GLenum mode, const GLsizei *count,
                                      GLenum type,
                                      const GLvoid * const *indices,
                                      GLsizei primcount,
                                      const GLint *basevertex)
{
   GLsizei i;

   for (i = 0; i < primcount; i++) {
      if (count[i] > 0) {
	 CALL_DrawElementsBaseVertex(GET_DISPATCH(), (mode, count[i], type,
						      indices[i],
						      basevertex[i]));
      }
   }
}
