external_bubble_state_set(void *data __UNUSED__, Evas_Object *obj, const void *from_params, const void *to_params, float pos __UNUSED__)
{
   const Elm_Params_Bubble *p;

   if (to_params) p = to_params;
   else if (from_params) p = from_params;
   else return;

   if (p->label) elm_object_text_set(obj, p->label);
   if (p->icon)
     elm_object_part_content_set(obj, "icon", p->icon);
   if (p->info) elm_object_part_text_set(obj, "info", p->info);
   if (p->content) elm_object_content_set(obj, p->content);
}
