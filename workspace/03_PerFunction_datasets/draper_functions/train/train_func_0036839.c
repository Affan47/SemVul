r200UpdateClipPlanes( struct gl_context *ctx )
{
   r200ContextPtr rmesa = R200_CONTEXT(ctx);
   GLuint p;

   for (p = 0; p < ctx->Const.MaxClipPlanes; p++) {
      if (ctx->Transform.ClipPlanesEnabled & (1 << p)) {
	 GLint *ip = (GLint *)ctx->Transform._ClipUserPlane[p];

	 R200_STATECHANGE( rmesa, ucp[p] );
	 rmesa->hw.ucp[p].cmd[UCP_X] = ip[0];
	 rmesa->hw.ucp[p].cmd[UCP_Y] = ip[1];
	 rmesa->hw.ucp[p].cmd[UCP_Z] = ip[2];
	 rmesa->hw.ucp[p].cmd[UCP_W] = ip[3];
      }
   }
}
