r200StencilFuncSeparate( struct gl_context *ctx, GLenum face, GLenum func,
                         GLint ref, GLuint mask )
{
   r200ContextPtr rmesa = R200_CONTEXT(ctx);
   GLuint refmask = ((_mesa_get_stencil_ref(ctx, 0) << R200_STENCIL_REF_SHIFT) |
		     ((ctx->Stencil.ValueMask[0] & 0xff) << R200_STENCIL_MASK_SHIFT));

   R200_STATECHANGE( rmesa, ctx );
   R200_STATECHANGE( rmesa, msk );

   rmesa->hw.ctx.cmd[CTX_RB3D_ZSTENCILCNTL] &= ~R200_STENCIL_TEST_MASK;
   rmesa->hw.msk.cmd[MSK_RB3D_STENCILREFMASK] &= ~(R200_STENCIL_REF_MASK|
						   R200_STENCIL_VALUE_MASK);

   switch ( ctx->Stencil.Function[0] ) {
   case GL_NEVER:
      rmesa->hw.ctx.cmd[CTX_RB3D_ZSTENCILCNTL] |= R200_STENCIL_TEST_NEVER;
      break;
   case GL_LESS:
      rmesa->hw.ctx.cmd[CTX_RB3D_ZSTENCILCNTL] |= R200_STENCIL_TEST_LESS;
      break;
   case GL_EQUAL:
      rmesa->hw.ctx.cmd[CTX_RB3D_ZSTENCILCNTL] |= R200_STENCIL_TEST_EQUAL;
      break;
   case GL_LEQUAL:
      rmesa->hw.ctx.cmd[CTX_RB3D_ZSTENCILCNTL] |= R200_STENCIL_TEST_LEQUAL;
      break;
   case GL_GREATER:
      rmesa->hw.ctx.cmd[CTX_RB3D_ZSTENCILCNTL] |= R200_STENCIL_TEST_GREATER;
      break;
   case GL_NOTEQUAL:
      rmesa->hw.ctx.cmd[CTX_RB3D_ZSTENCILCNTL] |= R200_STENCIL_TEST_NEQUAL;
      break;
   case GL_GEQUAL:
      rmesa->hw.ctx.cmd[CTX_RB3D_ZSTENCILCNTL] |= R200_STENCIL_TEST_GEQUAL;
      break;
   case GL_ALWAYS:
      rmesa->hw.ctx.cmd[CTX_RB3D_ZSTENCILCNTL] |= R200_STENCIL_TEST_ALWAYS;
      break;
   }

   rmesa->hw.msk.cmd[MSK_RB3D_STENCILREFMASK] |= refmask;
}
