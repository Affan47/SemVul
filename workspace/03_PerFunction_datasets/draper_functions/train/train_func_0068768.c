png_malloc_default(png_structp png_ptr, png_uint_32 size)
{
   png_voidp ret;
#endif

   if (png_ptr == NULL || size == 0)
      return (NULL);

#ifdef PNG_MAX_MALLOC_64K
   if (size > (png_uint_32)65536L)
   {
#ifndef PNG_USER_MEM_SUPPORTED
      if ((png_ptr->flags&PNG_FLAG_MALLOC_NULL_MEM_OK) == 0)
         png_error(png_ptr, "Cannot Allocate > 64K");
      else
#endif
         return NULL;
   }
#endif


#if defined(__TURBOC__) && !defined(__FLAT__)
   if (size != (unsigned long)size)
      ret = NULL;
   else
      ret = farmalloc(size);
#else
# if defined(_MSC_VER) && defined(MAXSEG_64K)
   if (size != (unsigned long)size)
      ret = NULL;
   else
      ret = halloc(size, 1);
# else
   if (size != (size_t)size)
      ret = NULL;
   else
      ret = malloc((size_t)size);
# endif
#endif

#ifndef PNG_USER_MEM_SUPPORTED
   if (ret == NULL && (png_ptr->flags&PNG_FLAG_MALLOC_NULL_MEM_OK) == 0)
      png_error(png_ptr, "Out of Memory");
#endif

   return (ret);
}
