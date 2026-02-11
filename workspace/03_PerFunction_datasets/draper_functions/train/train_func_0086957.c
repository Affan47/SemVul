evas_object_textblock_clear(Evas_Object *obj)
{
   TB_HEAD();
   _evas_object_textblock_clear_all(obj);


   evas_textblock_cursor_paragraph_first(o->cursor);
   evas_textblock_cursor_text_append(o->cursor, "");
}
