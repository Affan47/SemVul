png_get_x_offset_pixels(png_const_structrp png_ptr, png_const_inforp info_ptr)
{
#ifdef PNG_oFFs_SUPPORTED
   if (png_ptr != NULL && info_ptr != NULL && (info_ptr->valid & PNG_INFO_oFFs))
   {
      png_debug1(1, "in %s retrieval function", "png_get_x_offset_pixels");

      if (info_ptr->offset_unit_type == PNG_OFFSET_PIXEL)
         return (info_ptr->x_offset);
   }
#else
   PNG_UNUSED(png_ptr)
   PNG_UNUSED(info_ptr)
#endif

   return (0);
}
