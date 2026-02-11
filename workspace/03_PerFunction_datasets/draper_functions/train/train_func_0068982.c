elm_box_align_set(Evas_Object *obj,
                  double horizontal,
                  double vertical)
{
   ELM_BOX_CHECK(obj);
   ELM_BOX_DATA_GET(obj, sd);

   evas_object_size_hint_align_set
     (ELM_WIDGET_DATA(sd)->resize_obj, horizontal, vertical);
}
