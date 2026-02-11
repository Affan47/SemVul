set(struct brw_context *brw,
                            struct intel_mipmap_tree *mt,
                            unsigned int level, unsigned int layer,
                            bool is_render_target)
{
   brw_blorp_mip_info::set(mt, level, layer);
   this->num_samples = mt->num_samples;
   this->array_spacing_lod0 = mt->array_spacing_lod0;
   this->map_stencil_as_y_tiled = false;
   this->msaa_layout = mt->msaa_layout;

   switch (mt->format) {
   case MESA_FORMAT_S_UINT8:


      this->map_stencil_as_y_tiled = true;
      this->brw_surfaceformat = BRW_SURFACEFORMAT_R8_UNORM;
      break;
   case MESA_FORMAT_Z24_UNORM_X8_UINT:


      this->brw_surfaceformat = BRW_SURFACEFORMAT_B8G8R8A8_UNORM;
      break;
   case MESA_FORMAT_Z_FLOAT32:
      this->brw_surfaceformat = BRW_SURFACEFORMAT_R32_FLOAT;
      break;
   case MESA_FORMAT_Z_UNORM16:
      this->brw_surfaceformat = BRW_SURFACEFORMAT_R16_UNORM;
      break;
   default: {
      mesa_format linear_format = _mesa_get_srgb_format_linear(mt->format);
      if (is_render_target) {
         assert(brw->format_supported_as_render_target[linear_format]);
         this->brw_surfaceformat = brw->render_target_format[linear_format];
      } else {
         this->brw_surfaceformat = brw_format_for_mesa_format(linear_format);
      }
      break;
   }
   }
}
