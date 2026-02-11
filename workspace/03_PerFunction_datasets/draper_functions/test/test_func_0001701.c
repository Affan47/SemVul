evas_image_load_file_data_jpeg(Image_Entry *ie,
                               const char *file, const char *key __UNUSED__,
                               int *error)
{
   Eina_File *f;
   void *map;
   Eina_Bool val = EINA_FALSE;

   f = eina_file_open(file, EINA_FALSE);
   if (!f)
     {
	*error = EVAS_LOAD_ERROR_DOES_NOT_EXIST;
	return EINA_FALSE;
     }
   map = eina_file_map_all(f, EINA_FILE_WILLNEED);
   if (!map)
     {
        *error = EVAS_LOAD_ERROR_DOES_NOT_EXIST;
        goto on_error;
     }

   val = evas_image_load_file_data_jpeg_internal(ie,
                                                 map, eina_file_size_get(f),
                                                 error);

   eina_file_map_free(f, map);

 on_error:
   eina_file_close(f);
   return val;
}
