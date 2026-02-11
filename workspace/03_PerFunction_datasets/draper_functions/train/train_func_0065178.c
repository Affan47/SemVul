intel_get_non_msrt_mcs_alignment(struct brw_context *brw,
                                 struct intel_mipmap_tree *mt,
                                 unsigned *width_px, unsigned *height)
{
   switch (mt->region->tiling) {
   default:
      assert(!"Non-MSRT MCS requires X or Y tiling");

   case I915_TILING_Y:
      *width_px = 32 / mt->cpp;
      *height = 4;
      break;
   case I915_TILING_X:
      *width_px = 64 / mt->cpp;
      *height = 2;
   }
}
