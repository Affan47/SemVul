intel_miptree_downsample(struct brw_context *brw,
                         struct intel_mipmap_tree *mt)
{

   assert_is_flat(mt);

   if (!mt->need_downsample)
      return;
   intel_miptree_updownsample(brw,
                              mt, mt->singlesample_mt,
                              mt->logical_width0,
                              mt->logical_height0);
   mt->need_downsample = false;
}
