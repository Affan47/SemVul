validate_lighting( struct gl_context *ctx,
					struct tnl_pipeline_stage *stage )
{
   light_func *tab;

   if (!ctx->Light.Enabled || ctx->VertexProgram._Current)
      return;

   if (ctx->Light._NeedVertices) {
      if (ctx->Light.Model.ColorControl == GL_SEPARATE_SPECULAR_COLOR)
	 tab = _tnl_light_spec_tab;
      else
	 tab = _tnl_light_tab;
   }
   else {
      if (ctx->Light.EnabledList.next == ctx->Light.EnabledList.prev)
	 tab = _tnl_light_fast_single_tab;
      else
	 tab = _tnl_light_fast_tab;
   }


   LIGHT_STAGE_DATA(stage)->light_func_tab = tab;


   TNL_CONTEXT(ctx)->Driver.NotifyMaterialChange( ctx );
}
