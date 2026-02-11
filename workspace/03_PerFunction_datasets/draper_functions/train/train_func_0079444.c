evas_object_textblock_legacy_newline_set(Evas_Object *obj, Eina_Bool mode)
{
   TB_HEAD();
   if (o->legacy_newline == mode)
      return;

   o->legacy_newline = mode;


}
