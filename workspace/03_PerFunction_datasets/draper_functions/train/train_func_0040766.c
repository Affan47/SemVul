gen6_upload_sf_vp(struct brw_context *brw)
{
   struct gl_context *ctx = &brw->ctx;
   const GLfloat depth_scale = 1.0F / ctx->DrawBuffer->_DepthMaxF;
   struct brw_sf_viewport *sfv;
   GLfloat y_scale, y_bias;
   const bool render_to_fbo = _mesa_is_user_fbo(ctx->DrawBuffer);
   const GLfloat *v = ctx->ViewportArray[0]._WindowMap.m;

   sfv = brw_state_batch(brw, AUB_TRACE_SF_VP_STATE,
			 sizeof(*sfv), 32, &brw->sf.vp_offset);
   memset(sfv, 0, sizeof(*sfv));


   if (render_to_fbo) {
      y_scale = 1.0;
      y_bias = 0;
   } else {
      y_scale = -1.0;
      y_bias = ctx->DrawBuffer->Height;
   }


   sfv->viewport.m00 = v[MAT_SX];
   sfv->viewport.m11 = v[MAT_SY] * y_scale;
   sfv->viewport.m22 = v[MAT_SZ] * depth_scale;
   sfv->viewport.m30 = v[MAT_TX];
   sfv->viewport.m31 = v[MAT_TY] * y_scale + y_bias;
   sfv->viewport.m32 = v[MAT_TZ] * depth_scale;

   brw->state.dirty.cache |= CACHE_NEW_SF_VP;
}
