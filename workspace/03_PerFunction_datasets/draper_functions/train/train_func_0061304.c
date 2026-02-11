evas_object_textgrid_rows_clear(Evas_Object *obj)
{
   Evas_Object_Textgrid *o;
   int i;

   o = (Evas_Object_Textgrid *)(obj->object_data);
   if (!o->cur.rows) return;
   for (i = 0; i < o->cur.h; i++)
     {
        evas_object_textgrid_row_clear(o, &(o->cur.rows[i]));
        o->cur.rows[i].ch1 = 0;
        o->cur.rows[i].ch2 = o->cur.w - 1;
     }
}
