convert_half_to_float(const struct gl_client_array *input,
		      const GLubyte *ptr, GLfloat *fptr,
		      GLuint count, GLuint sz)
{
   GLuint i, j;

   for (i = 0; i < count; i++) {
      GLhalfARB *in = (GLhalfARB *)ptr;

      for (j = 0; j < sz; j++) {
	 *fptr++ = _mesa_half_to_float(in[j]);
      }
      ptr += input->StrideB;
   }
}
