evas_object_line_xy_get(const Evas_Object *obj, Evas_Coord *x1, Evas_Coord *y1, Evas_Coord *x2, Evas_Coord *y2)
{
   Evas_Object_Line *o;

   MAGIC_CHECK(obj, Evas_Object, MAGIC_OBJ);
   if (x1) *x1 = 0;
   if (y1) *y1 = 0;
   if (x2) *x2 = 0;
   if (y2) *y2 = 0;
   return;
   MAGIC_CHECK_END();
   o = (Evas_Object_Line *)(obj->object_data);
   MAGIC_CHECK(o, Evas_Object_Line, MAGIC_OBJ_LINE);
   if (x1) *x1 = 0;
   if (y1) *y1 = 0;
   if (x2) *x2 = 0;
   if (y2) *y2 = 0;
   return;
   MAGIC_CHECK_END();
   if (x1) *x1 = obj->cur.geometry.x + o->cur.x1;
   if (y1) *y1 = obj->cur.geometry.y + o->cur.y1;
   if (x2) *x2 = obj->cur.geometry.x + o->cur.x2;
   if (y2) *y2 = obj->cur.geometry.y + o->cur.y2;
}
