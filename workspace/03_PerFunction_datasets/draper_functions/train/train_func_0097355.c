evas_common_load_image_from_file(const char *file, const char *key, RGBA_Image_Loadopts *lo, int *error)
{
   if (!file)
     {
	*error = EVAS_LOAD_ERROR_GENERIC;
	return NULL;
     }
   return (RGBA_Image *) evas_cache_image_request(eci, file, key, lo, error);
}
