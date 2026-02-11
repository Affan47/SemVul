evas_object_text_glow2_color_set(Evas_Object *obj, int r, int g, int b, int a)
{
   Evas_Object_Text *o;

   MAGIC_CHECK(obj, Evas_Object, MAGIC_OBJ);
   return;
   MAGIC_CHECK_END();
   o = (Evas_Object_Text *)(obj->object_data);
   MAGIC_CHECK(o, Evas_Object_Text, MAGIC_OBJ_TEXT);
   return;
   MAGIC_CHECK_END();
   if ((o->cur.glow2.r == r) && (o->cur.glow2.g == g) &&
       (o->cur.glow2.b == b) && (o->cur.glow2.a == a))
     return;
   o->cur.glow2.r = r;
   o->cur.glow2.g = g;
   o->cur.glow2.b = b;
   o->cur.glow2.a = a;
   o->changed = 1;
   evas_object_change(obj);
}
