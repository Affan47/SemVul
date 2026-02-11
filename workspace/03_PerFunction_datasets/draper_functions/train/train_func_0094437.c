update_multisample(struct gl_context *ctx)
{
   ctx->Multisample._Enabled = GL_FALSE;
   if (ctx->Multisample.Enabled &&
       ctx->DrawBuffer &&
       ctx->DrawBuffer->Visual.sampleBuffers)
      ctx->Multisample._Enabled = GL_TRUE;
}
