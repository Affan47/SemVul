_block_clicked_cb(void *data __UNUSED__, Evas_Object *obj,
                  void *event_info __UNUSED__)
{
   printf("\nblock,clicked callback\n");
   Evas_Object *popup_data = evas_object_data_get(obj, "im");
   if (popup_data) evas_object_del(popup_data);
   evas_object_del(obj);
}
