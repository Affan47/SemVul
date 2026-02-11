_mark_new(Evas_Object *obj,
          const char *mark_type,
          struct tm *mark_time,
          Elm_Calendar_Mark_Repeat_Type repeat)
{
   Elm_Calendar_Mark *mark;

   mark = calloc(1, sizeof(Elm_Calendar_Mark));
   if (!mark) return NULL;
   mark->obj = obj;
   mark->mark_type = eina_stringshare_add(mark_type);
   mark->mark_time = *mark_time;
   mark->repeat = repeat;

   return mark;
}
