_e_smart_clip_set(Evas_Object *obj, Evas_Object *clip)
{
   INTERNAL_ENTRY;
   evas_object_clip_set(sd->edje_obj, clip);
   evas_object_clip_set(sd->event_obj, clip);
}
