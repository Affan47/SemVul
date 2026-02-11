_mesa_scissor_bounding_box(const struct gl_context *ctx,
                           const struct gl_framebuffer *buffer,
                           unsigned idx, int *bbox)
{
   bbox[0] = 0;
   bbox[2] = 0;
   bbox[1] = buffer->Width;
   bbox[3] = buffer->Height;

   if (ctx->Scissor.EnableFlags & (1u << idx)) {
      if (ctx->Scissor.ScissorArray[idx].X > bbox[0]) {
         bbox[0] = ctx->Scissor.ScissorArray[idx].X;
      }
      if (ctx->Scissor.ScissorArray[idx].Y > bbox[2]) {
         bbox[2] = ctx->Scissor.ScissorArray[idx].Y;
      }
      if (ctx->Scissor.ScissorArray[idx].X + ctx->Scissor.ScissorArray[idx].Width < bbox[1]) {
         bbox[1] = ctx->Scissor.ScissorArray[idx].X + ctx->Scissor.ScissorArray[idx].Width;
      }
      if (ctx->Scissor.ScissorArray[idx].Y + ctx->Scissor.ScissorArray[idx].Height < bbox[3]) {
         bbox[3] = ctx->Scissor.ScissorArray[idx].Y + ctx->Scissor.ScissorArray[idx].Height;
      }

      if (bbox[0] > bbox[1]) {
         bbox[0] = bbox[1];
      }
      if (bbox[2] > bbox[3]) {
         bbox[2] = bbox[3];
      }
   }

   ASSERT(bbox[0] <= bbox[1]);
   ASSERT(bbox[2] <= bbox[3]);
}
