intel_render_texture(struct gl_context * ctx,
                     struct gl_framebuffer *fb,
                     struct gl_renderbuffer_attachment *att)
{
   struct intel_context *intel = intel_context(ctx);
   struct gl_renderbuffer *rb = att->Renderbuffer;
   struct intel_renderbuffer *irb = intel_renderbuffer(rb);
   struct gl_texture_image *image = rb->TexImage;
   struct intel_texture_image *intel_image = intel_texture_image(image);
   struct intel_mipmap_tree *mt = intel_image->mt;
   int layer;

   (void) fb;

   if (att->CubeMapFace > 0) {
      assert(att->Zoffset == 0);
      layer = att->CubeMapFace;
   } else {
      layer = att->Zoffset;
   }

   if (!intel_image->mt) {


      _swrast_render_texture(ctx, fb, att);
      return;
   }

   intel_miptree_check_level_layer(mt, att->TextureLevel, layer);

   if (!intel_renderbuffer_update_wrapper(intel, irb, image, layer)) {
       _swrast_render_texture(ctx, fb, att);
       return;
   }

   DBG("Begin render %s texture tex=%u w=%d h=%d d=%d refcount=%d\n",
       _mesa_get_format_name(image->TexFormat),
       att->Texture->Name, image->Width, image->Height, image->Depth,
       rb->RefCount);


   intel_draw_buffer(ctx);
}
