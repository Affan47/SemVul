evas_image_max_size_get(const Evas *e, int *maxw, int *maxh)
{
   int w = 0, h = 0;
   MAGIC_CHECK(e, Evas, MAGIC_EVAS);
   return EINA_FALSE;
   MAGIC_CHECK_END();

   if (maxw) *maxw = 0xffff;
   if (maxh) *maxh = 0xffff;
   if (!e->engine.func->image_max_size_get) return EINA_FALSE;
   e->engine.func->image_max_size_get(e->engine.data.output, &w, &h);
   if (maxw) *maxw = w;
   if (maxh) *maxh = h;
   return EINA_TRUE;
}
