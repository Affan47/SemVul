_win_del_req(void *data, Evas_Object *obj __UNUSED__,
      void *event_info __UNUSED__)
{
   Photo_Object **photo_array = (Photo_Object **) data;

   if (!photo_array)
      return;


   for ( ; *photo_array ; photo_array++)
      free(*photo_array);

   free(data);
}
