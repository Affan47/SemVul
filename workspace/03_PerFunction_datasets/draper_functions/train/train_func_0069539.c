_resize_button(Evas_Object *btn, Evas_Coord *realw, Evas_Coord *vieww)
{
   Evas_Coord rw, vw;
   Evas_Coord w_text, h_btn, padding_outer = 0;
   Evas_Coord w_btn = 0, button_max_width = 0;
   const char *size_str;

   size_str = edje_object_data_get(btn, "button_max_size");
   if (size_str) button_max_width = (Evas_Coord)atoi(size_str);


   edje_object_part_geometry_get(btn, "elm.base", NULL, NULL, NULL, &h_btn);
   edje_object_part_geometry_get(btn, "elm.btn.text", NULL, NULL, &w_text, NULL);
   edje_object_part_geometry_get(btn, "right.padding", NULL, NULL, &padding_outer, NULL);
   w_btn = w_text + (2 * padding_outer);

   rw = w_btn;

   if (button_max_width < w_btn)
     vw = button_max_width;
   else
     vw = w_btn;


   evas_object_resize(btn, vw, h_btn);
   evas_object_size_hint_min_set(btn, vw, h_btn);

   if (realw) *realw = rw;
   if (vieww) *vieww = vw;
}
