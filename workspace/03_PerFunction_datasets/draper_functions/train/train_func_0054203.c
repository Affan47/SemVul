_tt_item_icon3(void *data   __UNUSED__,
              Evas_Object *obj __UNUSED__,
              Evas_Object *tt,
              void *item   __UNUSED__)
{
   int w, h, sw, sh;
   Evas_Object *ic = elm_icon_add(tt);

   char buf[PATH_MAX];
   snprintf(buf, sizeof(buf), "%s/images/insanely_huge_test_image.jpg", elm_app_data_dir_get());
   elm_image_file_set(ic, buf, NULL);
   elm_image_object_size_get(ic, &w, &h);
   elm_image_resizable_set(ic, 0, 0);
   elm_win_screen_size_get(tt, NULL, NULL, &sw, &sh);
   if ((w > sw) || (h > sh))
     {
        float sc = 0;
        if ((float)w / (float)sw >= 0.8)
          sc = ((float)sw * 0.8) / (float)w;
        else if ((float)h / (float)sh >= 0.8)
          sc = ((float)sh * 0.8) / (float)h;
        if (sc) elm_object_scale_set(ic, sc);
     }
   return ic;
}
