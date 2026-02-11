eng_image_can_region_get(void *data __UNUSED__, void *image)
{
   Image_Entry *im;
   if (!image) return EINA_FALSE;
#ifdef EVAS_CSERVE2
   if (evas_cserve2_use_get())
     return EINA_FALSE;
#endif
   im = image;
   return ((Evas_Image_Load_Func*) im->info.loader)->do_region;
}
