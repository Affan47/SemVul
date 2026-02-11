_mesa_dlist_alloc(struct gl_context *ctx, GLuint opcode, GLuint bytes)
{
   Node *n = dlist_alloc(ctx, (OpCode) opcode, bytes);
   if (n)
      return n + 1;
   else
      return NULL;
}
