png_destroy_read_struct(png_structpp png_ptr_ptr, png_infopp info_ptr_ptr,
   png_infopp end_info_ptr_ptr)
{
   png_structp png_ptr = NULL;
   png_infop info_ptr = NULL, end_info_ptr = NULL;
#ifdef PNG_USER_MEM_SUPPORTED
   png_free_ptr free_fn = NULL;
   png_voidp mem_ptr = NULL;
#endif

   png_debug(1, "in png_destroy_read_struct");

   if (png_ptr_ptr != NULL)
      png_ptr = *png_ptr_ptr;
   if (png_ptr == NULL)
      return;

#ifdef PNG_USER_MEM_SUPPORTED
   free_fn = png_ptr->free_fn;
   mem_ptr = png_ptr->mem_ptr;
#endif

   if (info_ptr_ptr != NULL)
      info_ptr = *info_ptr_ptr;

   if (end_info_ptr_ptr != NULL)
      end_info_ptr = *end_info_ptr_ptr;

   png_read_destroy(png_ptr, info_ptr, end_info_ptr);

   if (info_ptr != NULL)
   {
#ifdef PNG_TEXT_SUPPORTED
      png_free_data(png_ptr, info_ptr, PNG_FREE_TEXT, -1);
#endif

#ifdef PNG_USER_MEM_SUPPORTED
      png_destroy_struct_2((png_voidp)info_ptr, (png_free_ptr)free_fn,
          (png_voidp)mem_ptr);
#else
      png_destroy_struct((png_voidp)info_ptr);
#endif
      *info_ptr_ptr = NULL;
   }

   if (end_info_ptr != NULL)
   {
#ifdef PNG_READ_TEXT_SUPPORTED
      png_free_data(png_ptr, end_info_ptr, PNG_FREE_TEXT, -1);
#endif
#ifdef PNG_USER_MEM_SUPPORTED
      png_destroy_struct_2((png_voidp)end_info_ptr, (png_free_ptr)free_fn,
         (png_voidp)mem_ptr);
#else
      png_destroy_struct((png_voidp)end_info_ptr);
#endif
      *end_info_ptr_ptr = NULL;
   }

   if (png_ptr != NULL)
   {
#ifdef PNG_INDEX_SUPPORTED
      if (png_ptr->index) {
         unsigned int i, p;
         png_indexp index = png_ptr->index;
         for (p = 0; p < 7; p++) {
            for (i = 0; i < index->size[p]; i++) {
               inflateEnd(index->pass_line_index[p][i]->z_state);
               png_free(png_ptr, index->pass_line_index[p][i]->z_state);
               png_free(png_ptr, index->pass_line_index[p][i]->prev_row);
               png_free(png_ptr, index->pass_line_index[p][i]);
            }
            if (index->size[p] != 0) {
               png_free(png_ptr, index->pass_line_index[p]);
            }
         }
         png_free(png_ptr, index);
      }
#endif
#ifdef PNG_USER_MEM_SUPPORTED
      png_destroy_struct_2((png_voidp)png_ptr, (png_free_ptr)free_fn,
          (png_voidp)mem_ptr);
#else
      png_destroy_struct((png_voidp)png_ptr);
#endif
      *png_ptr_ptr = NULL;
   }
}
