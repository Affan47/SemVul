r200_validate_texture(struct gl_context *ctx, struct gl_texture_object *texObj, int unit)
{
   r200ContextPtr rmesa = R200_CONTEXT(ctx);
   radeonTexObj *t = radeon_tex_obj(texObj);

   if (!radeon_validate_texture_miptree(ctx, _mesa_get_samplerobj(ctx, unit), texObj))
      return GL_FALSE;

   r200_validate_texgen(ctx, unit);


   setup_hardware_state(rmesa, t);

   if (texObj->Target == GL_TEXTURE_RECTANGLE_NV ||
       texObj->Target == GL_TEXTURE_2D ||
       texObj->Target == GL_TEXTURE_1D)
      set_re_cntl_d3d( ctx, unit, GL_FALSE );
   else
      set_re_cntl_d3d( ctx, unit, GL_TRUE );
   R200_STATECHANGE( rmesa, ctx );
   rmesa->hw.ctx.cmd[CTX_PP_CNTL] |= R200_TEX_0_ENABLE << unit;

   R200_STATECHANGE( rmesa, vtx );
   rmesa->hw.vtx.cmd[VTX_TCL_OUTPUT_VTXFMT_1] &= ~(7 << (unit * 3));
   rmesa->hw.vtx.cmd[VTX_TCL_OUTPUT_VTXFMT_1] |= 4 << (unit * 3);

   rmesa->recheck_texgen[unit] = GL_TRUE;
   r200TexUpdateParameters(ctx, unit);
   import_tex_obj_state( rmesa, unit, t );

   if (rmesa->recheck_texgen[unit]) {
      GLboolean fallback = !r200_validate_texgen( ctx, unit );
      TCL_FALLBACK( ctx, (R200_TCL_FALLBACK_TEXGEN_0<<unit), fallback);
      rmesa->recheck_texgen[unit] = 0;
      rmesa->radeon.NewGLState |= _NEW_TEXTURE_MATRIX;
   }

   t->validated = GL_TRUE;

   FALLBACK( rmesa, RADEON_FALLBACK_BORDER_MODE, t->border_fallback );

   return !t->border_fallback;
}
