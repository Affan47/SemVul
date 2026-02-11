png_malloc(png_structp png_ptr, png_uint_32 size)
{
   png_voidp ret;

#ifdef PNG_USER_MEM_SUPPORTED
   if (png_ptr == NULL || size == 0)
      return (NULL);

   if (png_ptr->malloc_fn != NULL)
      ret = ((png_voidp)(*(png_ptr->malloc_fn))(png_ptr, (png_size_t)size));
   else
      ret = (png_malloc_default(png_ptr, size));
   if (ret == NULL && (png_ptr->flags&PNG_FLAG_MALLOC_NULL_MEM_OK) == 0)
       png_error(png_ptr, "Out of Memory!");
   return (ret);
}
