_parking_cb(void *data __UNUSED__, Evas_Object *map, Elm_Map_Overlay *ovl)
{
   double lon, lat;
   Evas_Coord x, y;
   elm_map_overlay_region_get(ovl, &lon, &lat);
   elm_map_region_to_canvas_convert(map, lon, lat, &x, &y);
   printf("Parking clicked: %lf %lf %d %d\n", lon, lat, x, y);

   elm_map_canvas_to_region_convert(map, x+40, y+50, &lon, &lat);
   if (!bubble_parking)
     {
        Evas_Object *bubble, *label;
        bubble = elm_bubble_add(map);
        elm_bubble_pos_set(bubble, ELM_BUBBLE_POS_TOP_LEFT);
        elm_object_text_set(bubble, "Overlay object");
        elm_object_part_text_set(bubble, "info", "Bubble is overlayed");

        label = elm_label_add(bubble);
        elm_object_text_set(label, "Parking Here !!");
        evas_object_show(label);
        elm_object_content_set(bubble, label);

        evas_object_resize(bubble, 125, 50);
        evas_object_show(bubble);

        bubble_parking = elm_map_overlay_add(map, lon, lat);
        elm_map_overlay_content_set(bubble_parking, bubble);
     }
   else elm_map_overlay_region_set(bubble_parking, lon, lat);
   elm_map_overlay_data_set(bubble_parking, ovl);
}
