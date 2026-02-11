evas_cache_image_data_not_needed(Image_Entry *im)
{
   int references;

   references = im->references;
   if (references > 1) return;
   if ((im->flags.dirty) || (!im->flags.need_data)) return;
   _evas_cache_image_lru_nodata_add(im);
}
