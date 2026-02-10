r200LightModelfv( struct gl_context *ctx, GLenum pname,
				const GLfloat *param )
{
   r200ContextPtr rmesa = R200_CONTEXT(ctx);

   switch (pname) {
      case GL_LIGHT_MODEL_AMBIENT:
	 update_global_ambient( ctx );
	 break;

      case GL_LIGHT_MODEL_LOCAL_VIEWER:
	 r200UpdateLocalViewer( ctx );
         break;

      case GL_LIGHT_MODEL_TWO_SIDE:
	 R200_STATECHANGE( rmesa, tcl );
	 if (ctx->Light.Model.TwoSide)
	    rmesa->hw.tcl.cmd[TCL_LIGHT_MODEL_CTL_0] |= R200_LIGHT_TWOSIDE;
	 else
	    rmesa->hw.tcl.cmd[TCL_LIGHT_MODEL_CTL_0] &= ~(R200_LIGHT_TWOSIDE);
	 if (rmesa->radeon.TclFallback) {
	    r200ChooseRenderState( ctx );
	    r200ChooseVertexState( ctx );
	 }
         break;

      case GL_LIGHT_MODEL_COLOR_CONTROL:
	 r200UpdateSpecular(ctx);
         break;

      default:
         break;
   }
}
