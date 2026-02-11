_elm_naviframe_smart_text_set(Evas_Object *obj,
                              const char *part,
                              const char *label)
{
   Elm_Object_Item *it;

   it = elm_naviframe_top_item_get(obj);
   if (!it) return EINA_FALSE;

   elm_object_item_part_text_set(it, part, label);

   return !strcmp(elm_object_item_part_text_get(it, part), label);
}
