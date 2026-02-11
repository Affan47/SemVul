_e_smart_clip_set(Evas_Object *obj, Evas_Object * clip)
{
   INTERNAL_ENTRY;
   evas_object_clip_set(sd->event_obj, clip);
   if (sd->o1) evas_object_clip_set(sd->o1, clip);
   if (sd->o2) evas_object_clip_set(sd->o2, clip);
}
