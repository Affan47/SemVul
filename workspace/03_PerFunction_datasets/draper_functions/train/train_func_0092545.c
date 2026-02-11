write_record(struct gl_context *ctx, GLuint value)
{
   if (ctx->Select.BufferCount < ctx->Select.BufferSize) {
      ctx->Select.Buffer[ctx->Select.BufferCount] = value;
   }
   ctx->Select.BufferCount++;
}
