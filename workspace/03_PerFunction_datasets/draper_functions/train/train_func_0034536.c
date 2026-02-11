_e_typebuf_add(Evas_Object *obj, const char *s)
{
   int len;

   INTERNAL_ENTRY;

   if (!sd->typebuf.buf)
     {
        sd->typebuf.buf = malloc(16);
        if (sd->typebuf.buf)
          {
             sd->typebuf.size = 16;
             sd->typebuf.buf[0] = '\0';
          }
        else
          {
             _e_typebuf_clean(obj);
             return;
          }
     }

   len = strlen(sd->typebuf.buf);
   if (len + strlen(s) + 2 + 1 >= sd->typebuf.size)
     {
        char *p = realloc(sd->typebuf.buf, sd->typebuf.size + strlen(s) + 16);
        if (p)
          {
             sd->typebuf.buf = p;
             sd->typebuf.size = sd->typebuf.size + strlen(s) + 16;
          }
        else
          {
             _e_typebuf_clean(obj);
             return;
          }
     }

   strcat(sd->typebuf.buf, s);
   edje_object_part_text_set(sd->o_edje, "e.text.typebuf_label", sd->typebuf.buf);
   edje_object_signal_emit(sd->o_edje, "e,state,typebuf,start", "e");
   _e_typebuf_match(obj);
   _e_typebuf_timer_update(obj);
}
