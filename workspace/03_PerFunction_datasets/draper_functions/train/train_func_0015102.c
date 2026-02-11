_evas_common_rgba_image_delete(Image_Entry *ie)
{
   RGBA_Image *im = (RGBA_Image *)ie;

#ifdef BUILD_PIPE_RENDER
   evas_common_pipe_free(im);
#endif
   evas_common_rgba_image_scalecache_shutdown(&im->cache_entry);
   if (ie->info.module) evas_module_unref((Evas_Module *)ie->info.module);


#ifdef EVAS_CSERVE
   if (ie->data1) evas_cserve_image_free(ie);
#endif
#ifdef EVAS_CSERVE2
   if (ie->data1)
       ERR("Shouldn't reach this point since we are using cache2: '%s' '%s'",
           ie->file, ie->key);

#endif


   if (ie->frames)
     {
        Eina_List *l;
        Image_Entry_Frame *frame;
        EINA_LIST_FOREACH(ie->frames, l, frame)
          {
           if (frame)
             {
                if (frame->data) free(frame->data);
                if (frame->info) free(frame->info);
                free (frame);
             }
          }
     }
   free(im);
}
