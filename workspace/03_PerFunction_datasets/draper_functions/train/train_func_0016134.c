_mesa_GenTransformFeedbacks(GLsizei n, GLuint *names)
{
   GLuint first;
   GET_CURRENT_CONTEXT(ctx);

   if (n < 0) {
      _mesa_error(ctx, GL_INVALID_VALUE, "glGenTransformFeedbacks(n < 0)");
      return;
   }

   if (!names)
      return;


   first = _mesa_HashFindFreeKeyBlock(ctx->TransformFeedback.Objects, n);
   if (first) {
      GLsizei i;
      for (i = 0; i < n; i++) {
         struct gl_transform_feedback_object *obj
            = ctx->Driver.NewTransformFeedback(ctx, first + i);
         if (!obj) {
            _mesa_error(ctx, GL_OUT_OF_MEMORY, "glGenTransformFeedbacks");
            return;
         }
         names[i] = first + i;
         _mesa_HashInsert(ctx->TransformFeedback.Objects, first + i, obj);
      }
   }
   else {
      _mesa_error(ctx, GL_OUT_OF_MEMORY, "glGenTransformFeedbacks");
   }
}
