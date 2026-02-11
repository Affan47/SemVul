brw_blorp_clear_color(struct brw_context *brw, struct gl_framebuffer *fb,
                      bool partial_clear)
{
   for (unsigned buf = 0; buf < fb->_NumColorDrawBuffers; buf++) {
      struct gl_renderbuffer *rb = fb->_ColorDrawBuffers[buf];
      struct intel_renderbuffer *irb = intel_renderbuffer(rb);


      if (rb == NULL)
         continue;

      if (fb->MaxNumLayers > 0) {
         unsigned layer_multiplier =
            (irb->mt->msaa_layout == INTEL_MSAA_LAYOUT_UMS ||
             irb->mt->msaa_layout == INTEL_MSAA_LAYOUT_CMS) ?
            irb->mt->num_samples : 1;
         unsigned num_layers =
            irb->mt->level[irb->mt_level].depth / layer_multiplier;
         for (unsigned layer = 0; layer < num_layers; layer++) {
            if (!do_single_blorp_clear(brw, fb, rb, buf, partial_clear,
                                       layer * layer_multiplier)) {
               return false;
            }
         }
      } else {
         unsigned layer = irb->mt_layer;
         if (!do_single_blorp_clear(brw, fb, rb, buf, partial_clear, layer))
            return false;
      }

      intel_renderbuffer_set_needs_downsample(irb);
   }

   return true;
}
