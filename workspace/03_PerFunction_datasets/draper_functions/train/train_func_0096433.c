_mesa_free_attrib_data(struct gl_context *ctx)
{
   while (ctx->AttribStackDepth > 0) {
      struct gl_attrib_node *attr, *next;

      ctx->AttribStackDepth--;
      attr = ctx->AttribStack[ctx->AttribStackDepth];

      while (attr) {
         if (attr->kind == GL_TEXTURE_BIT) {
            struct texture_state *texstate = (struct texture_state*)attr->data;
            GLuint u, tgt;

            for (u = 0; u < ctx->Const.MaxTextureUnits; u++) {
               for (tgt = 0; tgt < NUM_TEXTURE_TARGETS; tgt++) {
                  _mesa_reference_texobj(&texstate->SavedTexRef[u][tgt], NULL);
               }
            }
            _mesa_reference_shared_state(ctx, &texstate->SharedRef, NULL);
         }
         else {

         }

         next = attr->next;
         free(attr->data);
         free(attr);
         attr = next;
      }
   }
}
