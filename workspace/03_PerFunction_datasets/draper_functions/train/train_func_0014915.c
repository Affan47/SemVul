evas_object_textblock_size_formatted_get(const Evas_Object *obj, Evas_Coord *w, Evas_Coord *h)
{
   TB_HEAD();
   if (!o->formatted.valid) _relayout(obj);
   if (w) *w = o->formatted.w;
   if (h) *h = o->formatted.h;
}
