_tnl_import_array( struct gl_context *ctx,
			       GLuint attrib,
			       GLuint count,
			       const struct gl_client_array *input,
			       const GLubyte *ptr )
{
   TNLcontext *tnl = TNL_CONTEXT(ctx);
   struct vertex_buffer *VB = &tnl->vb;
   GLuint stride = input->StrideB;

   if (input->Type != GL_FLOAT) {
      const GLuint sz = input->Size;
      GLubyte *buf = get_space(ctx, count * sz * sizeof(GLfloat));
      GLfloat *fptr = (GLfloat *)buf;

      switch (input->Type) {
      case GL_BYTE:
	 CONVERT(GLbyte, BYTE_TO_FLOAT);
	 break;
      case GL_UNSIGNED_BYTE:
         if (input->Format == GL_BGRA) {

            convert_bgra_to_float(input, ptr, fptr, count);
         }
         else {
            CONVERT(GLubyte, UBYTE_TO_FLOAT);
         }
	 break;
      case GL_SHORT:
	 CONVERT(GLshort, SHORT_TO_FLOAT);
	 break;
      case GL_UNSIGNED_SHORT:
	 CONVERT(GLushort, USHORT_TO_FLOAT);
	 break;
      case GL_INT:
	 CONVERT(GLint, INT_TO_FLOAT);
	 break;
      case GL_UNSIGNED_INT:
	 CONVERT(GLuint, UINT_TO_FLOAT);
	 break;
      case GL_DOUBLE:
	 CONVERT(GLdouble, (GLfloat));
	 break;
      case GL_HALF_FLOAT:
	 convert_half_to_float(input, ptr, fptr, count, sz);
	 break;
      case GL_FIXED:
         convert_fixed_to_float(input, ptr, fptr, count);
         break;
      default:
	 assert(0);
	 break;
      }

      ptr = buf;
      stride = sz * sizeof(GLfloat);
   }

   VB->AttribPtr[attrib] = &tnl->tmp_inputs[attrib];
   VB->AttribPtr[attrib]->data = (GLfloat (*)[4])ptr;
   VB->AttribPtr[attrib]->start = (GLfloat *)ptr;
   VB->AttribPtr[attrib]->count = count;
   VB->AttribPtr[attrib]->stride = stride;
   VB->AttribPtr[attrib]->size = input->Size;


   VB->AttribPtr[attrib]->flags = (((1<<input->Size)-1) |
				   VEC_NOT_WRITEABLE |
				   (stride == 4*sizeof(GLfloat) ? 0 : VEC_BAD_STRIDE));

   VB->AttribPtr[attrib]->storage = NULL;
}
