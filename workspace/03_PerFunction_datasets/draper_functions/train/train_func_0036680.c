_mesa_lookup_renderbuffer(struct gl_context *ctx, GLuint id)
{
   struct gl_renderbuffer *rb;

   if (id == 0)
      return NULL;

   rb = (struct gl_renderbuffer *)
      _mesa_HashLookup(ctx->Shared->RenderBuffers, id);
   return rb;
}
