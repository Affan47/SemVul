evas_object_textgrid_size_set(Evas_Object *obj, int w, int h)
{
   Evas_Object_Textgrid *o;
   int i;

   if ((h <= 0) || (w <= 0)) return;

   MAGIC_CHECK(obj, Evas_Object, MAGIC_OBJ);
   return;
   MAGIC_CHECK_END();
   o = (Evas_Object_Textgrid *)(obj->object_data);
   MAGIC_CHECK(o, Evas_Object_Textgrid, MAGIC_OBJ_TEXTGRID);
   return;
   MAGIC_CHECK_END();

   if ((o->cur.w == w) && (o->cur.h == h)) return;

   evas_object_textgrid_rows_clear(obj);
   if (o->cur.rows)
     {
        free(o->cur.rows);
        o->cur.rows = NULL;
     }
   if (o->cur.cells)
     {
        free(o->cur.cells);
        o->cur.cells = NULL;
     }
   o->cur.cells = calloc(w * h, sizeof(Evas_Textgrid_Cell));
   if (!o->cur.cells) return;
   o->cur.rows = calloc(h, sizeof(Evas_Object_Textgrid_Row));
   if (!o->cur.rows)
     {
        free(o->cur.cells);
        o->cur.cells = NULL;
        return;
     }
   for (i = 0; i < h; i++)
     {
        o->cur.rows[i].ch1 = 0;
        o->cur.rows[i].ch2 = w - 1;
     }
   o->cur.w = w;
   o->cur.h = h;
   o->changed = 1;
   o->core_change = 1;
   evas_object_change(obj);
}
