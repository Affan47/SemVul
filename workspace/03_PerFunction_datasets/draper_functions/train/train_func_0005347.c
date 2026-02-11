_format_dup(Evas_Object *obj, const Evas_Object_Textblock_Format *fmt)
{
   Evas_Object_Textblock_Format *fmt2;

   fmt2 = calloc(1, sizeof(Evas_Object_Textblock_Format));
   memcpy(fmt2, fmt, sizeof(Evas_Object_Textblock_Format));
   fmt2->ref = 1;
   fmt2->font.fdesc = evas_font_desc_ref(fmt->font.fdesc);

   if (fmt->font.source) fmt2->font.source = eina_stringshare_add(fmt->font.source);


   fmt2->font.font = evas_font_load(obj->layer->evas, fmt2->font.fdesc,
         fmt2->font.source, (int)(((double) fmt2->font.size) * obj->cur.scale));
   return fmt2;
}
