_btn_clicked(void *data, Evas_Object *obj, void *event_info __UNUSED__)
{
   printf("Button Clicked\n");

   Evas_Object *im;
   char buf[PATH_MAX];
   void *ctxpopup_data;

   ctxpopup_data = evas_object_data_get(data, "id");
   if (!ctxpopup_data) return;

   if (!strcmp("list_item_6", (char *) ctxpopup_data))
     {
        ctxpopup_data = evas_object_data_get(data, "im");
        if (ctxpopup_data) return;

        im = evas_object_image_filled_add(evas_object_evas_get(obj));
        snprintf(buf, sizeof(buf), "%s/images/%s",
                 elm_app_data_dir_get(), "twofish.jpg");
        evas_object_image_file_set(im, buf, NULL);
        evas_object_move(im, 40, 40);
        evas_object_resize(im, 320, 320);
        evas_object_show(im);
        evas_object_data_set((Evas_Object *)data, "im", im);

        evas_object_raise((Evas_Object *)data);
     }
}
