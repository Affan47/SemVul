_evas_object_textblock_clear_all(Evas_Object *obj)
{
   Eina_List *l;
   Evas_Textblock_Cursor *cur;

   TB_HEAD();
   if (o->paragraphs)
     {
	_paragraphs_free(obj, o->paragraphs);
	o->paragraphs = NULL;
     }

   _nodes_clear(obj);
   o->cursor->node = NULL;
   o->cursor->pos = 0;
   EINA_LIST_FOREACH(o->cursors, l, cur)
     {
	cur->node = NULL;
	cur->pos = 0;

     }

   _evas_textblock_changed(o, obj);
}
