intel_miptree_copy_slice_sw(struct intel_context *intel,
                            struct intel_mipmap_tree *dst_mt,
                            struct intel_mipmap_tree *src_mt,
                            int level,
                            int slice,
                            int width,
                            int height)
{
   void *src, *dst;
   int src_stride, dst_stride;
   int cpp = dst_mt->cpp;

   intel_miptree_map(intel, src_mt,
                     level, slice,
                     0, 0,
                     width, height,
                     GL_MAP_READ_BIT,
                     &src, &src_stride);

   intel_miptree_map(intel, dst_mt,
                     level, slice,
                     0, 0,
                     width, height,
                     GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_RANGE_BIT,
                     &dst, &dst_stride);

   DBG("sw blit %s mt %p %p/%d -> %s mt %p %p/%d (%dx%d)\n",
       _mesa_get_format_name(src_mt->format),
       src_mt, src, src_stride,
       _mesa_get_format_name(dst_mt->format),
       dst_mt, dst, dst_stride,
       width, height);

   int row_size = cpp * width;
   if (src_stride == row_size &&
       dst_stride == row_size) {
      memcpy(dst, src, row_size * height);
   } else {
      for (int i = 0; i < height; i++) {
         memcpy(dst, src, row_size);
         dst += dst_stride;
         src += src_stride;
      }
   }

   intel_miptree_unmap(intel, dst_mt, level, slice);
   intel_miptree_unmap(intel, src_mt, level, slice);
}
