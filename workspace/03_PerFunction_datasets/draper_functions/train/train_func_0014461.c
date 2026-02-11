_fc_list_unselect_cb(void *data       __UNUSED__,
                     Evas_Object     *obj,
                     void *event_info __UNUSED__)
{
   Evas_Object *font_names_list, *styles_list, *sizes_list, *win;

   if (elm_list_selected_item_get(obj)) return;

   win = elm_object_top_widget_get(obj);

   font_names_list = evas_object_data_get(win, "font_names_list");
   ELM_LIST_DISABLE(font_names_list);

   styles_list = evas_object_data_get(win, "font_styles_list");
   ELM_LIST_DISABLE(styles_list);

   sizes_list = evas_object_data_get(win, "font_sizes_list");
   ELM_LIST_DISABLE(sizes_list);
}
