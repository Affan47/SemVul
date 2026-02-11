brw_predraw_resolve_buffers(struct brw_context *brw)
{
   struct gl_context *ctx = &brw->ctx;
   struct intel_renderbuffer *depth_irb;
   struct intel_texture_object *tex_obj;


   depth_irb = intel_get_renderbuffer(ctx->DrawBuffer, BUFFER_DEPTH);
   if (depth_irb)
      intel_renderbuffer_resolve_hiz(brw, depth_irb);


   for (int i = 0; i < ctx->Const.MaxCombinedTextureImageUnits; i++) {
      if (!ctx->Texture.Unit[i]._ReallyEnabled)
	 continue;
      tex_obj = intel_texture_object(ctx->Texture.Unit[i]._Current);
      if (!tex_obj || !tex_obj->mt)
	 continue;
      intel_miptree_all_slices_resolve_depth(brw, tex_obj->mt);
      intel_miptree_resolve_color(brw, tex_obj->mt);
   }
}
