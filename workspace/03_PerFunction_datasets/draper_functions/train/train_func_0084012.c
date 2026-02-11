_theme_data_get(Evas_Object *obj)
{
   const char *str;
   Evas_Object *blank;

   ELM_DISKSELECTOR_DATA_GET(obj, sd);

   blank = eina_list_data_get(sd->right_blanks);
   if (blank) return;

   str = edje_object_data_get(blank, "len_threshold");
   if (str) sd->len_threshold = MAX(0, atoi(str));
   else sd->len_threshold = 0;

   if (!sd->display_item_num_by_api)
     {
        str = edje_object_data_get(blank, "display_item_num");
        if (str)
          {
             sd->display_item_num = MAX(DISPLAY_ITEM_NUM_MIN, atoi(str));
             if (!sd->round) _blank_item_check(obj, sd->display_item_num);
          }

        else sd->display_item_num = DISPLAY_ITEM_NUM_MIN;
     }

   str = edje_object_data_get(blank, "min_width");
   if (str) sd->minw = MAX(-1, atoi(str));
   else sd->minw = -1;

   str = edje_object_data_get(blank, "min_height");
   if (str) sd->minh = MAX(-1, atoi(str));
   else sd->minh = -1;
}
