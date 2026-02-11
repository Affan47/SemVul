elm_colorselector_palette_item_color_set(Elm_Object_Item *it,
                                         int r,
                                         int g,
                                         int b,
                                         int a)
{
   Elm_Color_Item *item;

   ELM_COLORSELECTOR_ITEM_CHECK_OR_RETURN(it);

   item = (Elm_Color_Item *)it;
   item->color->r = r;
   item->color->g = g;
   item->color->b = b;
   item->color->a = a;
   evas_object_color_set
     (item->color_obj, item->color->r, item->color->g, item->color->b,
     item->color->a);

   _colors_save(WIDGET(it));
}
