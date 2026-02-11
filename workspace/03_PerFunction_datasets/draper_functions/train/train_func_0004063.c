_palette_colors_load(Evas_Object *obj)
{
   Eina_List *elist;
   Elm_Color_Item *item;
   Eina_List *color_list;
   Elm_Color_RGBA *color;

   ELM_COLORSELECTOR_DATA_GET(obj, sd);

   color_list = _elm_config_color_list_get(sd->palette_name);
   if (!color_list) return;

   EINA_LIST_FOREACH (color_list, elist, color)
     {
        item = _item_new(obj);
        if (!item) return;

        item->color = ELM_NEW(Elm_Color_RGBA);
        if (!item->color) return;
        item->color->r = color->r;
        item->color->g = color->g;
        item->color->b = color->b;
        item->color->a = color->a;

        elm_box_pack_end(sd->palette_box, VIEW(item));
        evas_object_color_set
          (item->color_obj, item->color->r, item->color->g, item->color->b,
          item->color->a);

        sd->items = eina_list_append(sd->items, item);
     }

   sd->config_load = EINA_TRUE;
}
