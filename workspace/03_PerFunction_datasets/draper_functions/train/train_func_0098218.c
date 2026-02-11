elm_photo_fill_inside_set(Evas_Object *obj,
                          Eina_Bool fill)
{
   ELM_PHOTO_CHECK(obj);
   ELM_PHOTO_DATA_GET(obj, sd);

   elm_image_fill_outside_set(sd->icon, !fill);
   sd->fill_inside = !!fill;

   _sizing_eval(obj);
}
