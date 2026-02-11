_elm_image_smart_clip_set(Evas_Object *obj,
                          Evas_Object *clip)
{
   ELM_IMAGE_DATA_GET(obj, sd);

   ELM_WIDGET_CLASS(_elm_image_parent_sc)->base.clip_set(obj, clip);

   evas_object_clip_set(sd->img, clip);
   if (sd->prev_img) evas_object_clip_set(sd->prev_img, clip);
}
