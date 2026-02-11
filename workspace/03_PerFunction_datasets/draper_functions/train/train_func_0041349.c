i830LineWidth(struct gl_context * ctx, GLfloat widthf)
{
   struct i830_context *i830 = i830_context(ctx);
   int width;
   int state5;

   DBG("%s\n", __FUNCTION__);

   width = (int) (widthf * 2);
   width = CLAMP(width, 1, 15);

   state5 = i830->state.Ctx[I830_CTXREG_STATE5] & ~FIXED_LINE_WIDTH_MASK;
   state5 |= (ENABLE_FIXED_LINE_WIDTH | FIXED_LINE_WIDTH(width));

   if (state5 != i830->state.Ctx[I830_CTXREG_STATE5]) {
      I830_STATECHANGE(i830, I830_UPLOAD_CTX);
      i830->state.Ctx[I830_CTXREG_STATE5] = state5;
   }
}
