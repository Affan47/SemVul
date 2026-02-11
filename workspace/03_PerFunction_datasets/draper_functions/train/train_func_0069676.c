transition_to_swtnl( struct gl_context *ctx )
{
   r200ContextPtr rmesa = R200_CONTEXT(ctx);
   TNLcontext *tnl = TNL_CONTEXT(ctx);

   R200_NEWPRIM( rmesa );

   r200ChooseVertexState( ctx );
   r200ChooseRenderState( ctx );

   _tnl_validate_shine_tables( ctx );

   tnl->Driver.NotifyMaterialChange =
      _tnl_validate_shine_tables;

   radeonReleaseArrays( ctx, ~0 );


   R200_STATECHANGE( rmesa, vap );
   rmesa->hw.vap.cmd[VAP_SE_VAP_CNTL] &= ~(R200_VAP_TCL_ENABLE|R200_VAP_PROG_VTX_SHADER_ENABLE);
}
