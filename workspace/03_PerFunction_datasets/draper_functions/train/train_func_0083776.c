png_get_valid(png_const_structrp png_ptr, png_const_inforp info_ptr,
    png_uint_32 flag)
{
   if (png_ptr != NULL && info_ptr != NULL)
      return(info_ptr->valid & flag);

   return(0);
}
