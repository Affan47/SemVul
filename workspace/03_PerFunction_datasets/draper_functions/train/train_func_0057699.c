elm_image_editable_set(Evas_Object *obj,
                       Eina_Bool set)
{
   ELM_IMAGE_CHECK(obj);
   ELM_IMAGE_DATA_GET(obj, sd);

   ELM_IMAGE_CLASS(ELM_WIDGET_DATA(sd)->api)->edit_set(obj, set, obj);
}
