bind_vertex_array(struct gl_context *ctx, GLuint id, GLboolean genRequired)
{
   struct gl_array_object * const oldObj = ctx->Array.ArrayObj;
   struct gl_array_object *newObj = NULL;

   ASSERT(oldObj != NULL);

   if ( oldObj->Name == id )
      return;


   if (id == 0) {


      newObj = ctx->Array.DefaultArrayObj;
   }
   else {

      newObj = _mesa_lookup_arrayobj(ctx, id);
      if (!newObj) {
         if (genRequired) {
            _mesa_error(ctx, GL_INVALID_OPERATION,
                        "glBindVertexArray(non-gen name)");
            return;
         }


	 newObj = (*ctx->Driver.NewArrayObject)(ctx, id);
         if (!newObj) {
            _mesa_error(ctx, GL_OUT_OF_MEMORY, "glBindVertexArrayAPPLE");
            return;
         }

         save_array_object(ctx, newObj);
      }

      if (!newObj->EverBound) {


         newObj->ARBsemantics = genRequired;
         newObj->EverBound = GL_TRUE;
      }
   }

   ctx->NewState |= _NEW_ARRAY;
   _mesa_reference_array_object(ctx, &ctx->Array.ArrayObj, newObj);


   if (ctx->Driver.BindArrayObject && newObj)
      ctx->Driver.BindArrayObject(ctx, newObj);
}
