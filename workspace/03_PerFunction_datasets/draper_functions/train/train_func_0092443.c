trim_list(struct gl_context *ctx)
{


   struct gl_dlist_state *list = &ctx->ListState;

   if ((list->CurrentList->Head == list->CurrentBlock) &&
       (list->CurrentPos < BLOCK_SIZE)) {

      GLuint newSize = list->CurrentPos * sizeof(Node);
      list->CurrentList->Head =
      list->CurrentBlock = realloc(list->CurrentBlock, newSize);
      if (!list->CurrentBlock) {
         _mesa_error(ctx, GL_OUT_OF_MEMORY, "glEndList");
      }
   }
}
