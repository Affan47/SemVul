brw_lower_packing_builtins(struct brw_context *brw,
                           gl_shader_stage shader_type,
                           exec_list *ir)
{
   int ops = LOWER_PACK_SNORM_2x16
           | LOWER_UNPACK_SNORM_2x16
           | LOWER_PACK_UNORM_2x16
           | LOWER_UNPACK_UNORM_2x16
           | LOWER_PACK_SNORM_4x8
           | LOWER_UNPACK_SNORM_4x8
           | LOWER_PACK_UNORM_4x8
           | LOWER_UNPACK_UNORM_4x8;

   if (brw->gen >= 7) {


      if (shader_type == MESA_SHADER_FRAGMENT) {
         ops |= LOWER_PACK_HALF_2x16_TO_SPLIT
             |  LOWER_UNPACK_HALF_2x16_TO_SPLIT;
      }
   } else {
      ops |= LOWER_PACK_HALF_2x16
          |  LOWER_UNPACK_HALF_2x16;
   }

   lower_packing_builtins(ir, ops);
}
