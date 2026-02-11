_elm_tooltip_trans_label_create(void *data, Evas_Object *obj __UNUSED__, Evas_Object *tooltip)
{
   Evas_Object *label = elm_label_add(tooltip);
   const char **text = data;
   if (!label)
     return NULL;
   elm_object_style_set(label, "tooltip");
   elm_object_domain_translatable_text_set(label, text[0], text[1]);
   return label;
}
