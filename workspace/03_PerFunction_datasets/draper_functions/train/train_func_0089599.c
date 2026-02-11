_reload_format(Evas_Object *obj)
{
   unsigned int idx, field_count;
   Datetime_Field *field;
   char buf[BUFFER_SIZE];
   char *dt_fmt;

   ELM_DATETIME_DATA_GET(obj, sd);


   if (!sd->user_format)
#ifdef HAVE_LANGINFO_H
     strncpy(sd->format, nl_langinfo(D_T_FMT), ELM_DATETIME_MAX_FORMAT_LEN);
#else
     strncpy(sd->format, "", ELM_DATETIME_MAX_FORMAT_LEN);
#endif

   dt_fmt = (char *)malloc(ELM_DATETIME_MAX_FORMAT_LEN);
   if (!dt_fmt) return;

   strncpy(dt_fmt, sd->format, ELM_DATETIME_MAX_FORMAT_LEN);

   _expand_format(dt_fmt);


   for (idx = 0; idx < ELM_DATETIME_TYPE_COUNT; idx++)
     {
        field = sd->field_list + idx;
        field->fmt_exist = EINA_FALSE;
        field->location = -1;
     }

   field_count = _parse_format(obj, dt_fmt);
   free(dt_fmt);


   for (idx = 0; idx < ELM_DATETIME_TYPE_COUNT; idx++)
     {
        field = sd->field_list + idx;
        if (field->location == -1) field->location = field_count++;

        if (field->fmt_exist && field->visible)
          {
             snprintf(buf, sizeof(buf), EDC_PART_FIELD_ENABLE_SIG_STR,
                      field->location);
             elm_layout_signal_emit(obj, buf, "elm");
          }
        else
          {
             snprintf(buf, sizeof(buf), EDC_PART_FIELD_DISABLE_SIG_STR,
                      field->location);
             elm_layout_signal_emit(obj, buf, "elm");
          }
        snprintf
          (buf, sizeof(buf), EDC_PART_SEPARATOR_STR, (field->location + 1));
        elm_layout_text_set(obj, buf, field->separator);
     }

   edje_object_message_signal_process(ELM_WIDGET_DATA(sd)->resize_obj);
   _field_list_arrange(obj);
}
