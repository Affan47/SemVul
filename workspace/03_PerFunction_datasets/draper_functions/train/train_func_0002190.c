replay_finish( struct copy_context *copy )
{
   struct gl_context *ctx = copy->ctx;
   GLuint i;


   free(copy->translated_elt_buf);
   free(copy->dstbuf);
   free(copy->dstelt);


   for (i = 0; i < copy->nr_varying; i++) {
      struct gl_buffer_object *vbo = copy->varying[i].array->BufferObj;
      if (_mesa_is_bufferobj(vbo) && _mesa_bufferobj_mapped(vbo))
	 ctx->Driver.UnmapBuffer(ctx, vbo);
   }


   if (_mesa_is_bufferobj(copy->ib->obj) &&
       _mesa_bufferobj_mapped(copy->ib->obj)) {
      ctx->Driver.UnmapBuffer(ctx, copy->ib->obj);
   }
}
