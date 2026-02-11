_swrast_choose_blend_func(struct gl_context *ctx, GLenum chanType)
{
   SWcontext *swrast = SWRAST_CONTEXT(ctx);
   const GLenum eq = ctx->Color.Blend[0].EquationRGB;
   const GLenum srcRGB = ctx->Color.Blend[0].SrcRGB;
   const GLenum dstRGB = ctx->Color.Blend[0].DstRGB;
   const GLenum srcA = ctx->Color.Blend[0].SrcA;
   const GLenum dstA = ctx->Color.Blend[0].DstA;

   if (ctx->Color.Blend[0].EquationRGB != ctx->Color.Blend[0].EquationA) {
      swrast->BlendFunc = blend_general;
   }
   else if (eq == GL_MIN) {

#if defined(USE_MMX_ASM)
      if (cpu_has_mmx && chanType == GL_UNSIGNED_BYTE) {
         swrast->BlendFunc = _mesa_mmx_blend_min;
      }
      else
#endif
         swrast->BlendFunc = blend_min;
   }
   else if (eq == GL_MAX) {

#if defined(USE_MMX_ASM)
      if (cpu_has_mmx && chanType == GL_UNSIGNED_BYTE) {
         swrast->BlendFunc = _mesa_mmx_blend_max;
      }
      else
#endif
         swrast->BlendFunc = blend_max;
   }
   else if (srcRGB != srcA || dstRGB != dstA) {
      swrast->BlendFunc = blend_general;
   }
   else if (eq == GL_FUNC_ADD && srcRGB == GL_SRC_ALPHA
            && dstRGB == GL_ONE_MINUS_SRC_ALPHA) {
#if defined(USE_MMX_ASM)
      if (cpu_has_mmx && chanType == GL_UNSIGNED_BYTE) {
         swrast->BlendFunc = _mesa_mmx_blend_transparency;
      }
      else
#endif
      {
         if (chanType == GL_UNSIGNED_BYTE)
            swrast->BlendFunc = blend_transparency_ubyte;
         else if (chanType == GL_UNSIGNED_SHORT)
            swrast->BlendFunc = blend_transparency_ushort;
         else
            swrast->BlendFunc = blend_transparency_float;
      }
   }
   else if (eq == GL_FUNC_ADD && srcRGB == GL_ONE && dstRGB == GL_ONE) {
#if defined(USE_MMX_ASM)
      if (cpu_has_mmx && chanType == GL_UNSIGNED_BYTE) {
         swrast->BlendFunc = _mesa_mmx_blend_add;
      }
      else
#endif
         swrast->BlendFunc = blend_add;
   }
   else if (((eq == GL_FUNC_ADD || eq == GL_FUNC_REVERSE_SUBTRACT)
	     && (srcRGB == GL_ZERO && dstRGB == GL_SRC_COLOR))
	    ||
	    ((eq == GL_FUNC_ADD || eq == GL_FUNC_SUBTRACT)
	     && (srcRGB == GL_DST_COLOR && dstRGB == GL_ZERO))) {
#if defined(USE_MMX_ASM)
      if (cpu_has_mmx && chanType == GL_UNSIGNED_BYTE) {
         swrast->BlendFunc = _mesa_mmx_blend_modulate;
      }
      else
#endif
         swrast->BlendFunc = blend_modulate;
   }
   else if (eq == GL_FUNC_ADD && srcRGB == GL_ZERO && dstRGB == GL_ONE) {
      swrast->BlendFunc = blend_noop;
   }
   else if (eq == GL_FUNC_ADD && srcRGB == GL_ONE && dstRGB == GL_ZERO) {
      swrast->BlendFunc = blend_replace;
   }
   else {
      swrast->BlendFunc = blend_general;
   }
}
