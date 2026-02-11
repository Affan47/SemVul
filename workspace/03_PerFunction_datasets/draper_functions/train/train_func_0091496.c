imImageMergeAttributes(const imImage* src_image, imImage* dst_image)
{
  assert(src_image);
  assert(dst_image);

  if (src_image->palette && dst_image->palette &&
      src_image->color_space == dst_image->color_space)
  {
    memcpy(dst_image->palette, src_image->palette, 256*sizeof(long));
    dst_image->palette_count = src_image->palette_count;
  }

  iAttributeTableMerge(src_image->attrib_table, dst_image->attrib_table);
}
