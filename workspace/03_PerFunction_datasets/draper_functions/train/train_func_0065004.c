do_stencil_test(struct gl_context *ctx, GLuint face, GLuint n,
                GLubyte stencil[], GLubyte mask[], GLint stride)
{
   SWcontext *swrast = SWRAST_CONTEXT(ctx);
   GLubyte *fail = swrast->stencil_temp.buf2;
   GLboolean allfail = GL_FALSE;
   GLuint i, j;
   const GLuint valueMask = ctx->Stencil.ValueMask[face];
   const GLubyte ref = (GLubyte) (_mesa_get_stencil_ref(ctx, face) & valueMask);
   GLubyte s;


   switch (ctx->Stencil.Function[face]) {
   case GL_NEVER:
      STENCIL_TEST(0);
      allfail = GL_TRUE;
      break;
   case GL_LESS:
      STENCIL_TEST(ref < s);
      break;
   case GL_LEQUAL:
      STENCIL_TEST(ref <= s);
      break;
   case GL_GREATER:
      STENCIL_TEST(ref > s);
      break;
   case GL_GEQUAL:
      STENCIL_TEST(ref >= s);
      break;
   case GL_EQUAL:
      STENCIL_TEST(ref == s);
      break;
   case GL_NOTEQUAL:
      STENCIL_TEST(ref != s);
      break;
   case GL_ALWAYS:
      STENCIL_TEST(1);
      break;
   default:
      _mesa_problem(ctx, "Bad stencil func in gl_stencil_span");
      return 0;
   }

   if (ctx->Stencil.FailFunc[face] != GL_KEEP) {
      apply_stencil_op(ctx, ctx->Stencil.FailFunc[face], face, n, stencil,
                       fail, stride);
   }

   return !allfail;
}
