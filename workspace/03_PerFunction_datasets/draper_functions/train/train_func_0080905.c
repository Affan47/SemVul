evas_damage_rectangle_add(Evas *e, int x, int y, int w, int h)
{
   Eina_Rectangle *r;

   MAGIC_CHECK(e, Evas, MAGIC_EVAS);
   return;
   MAGIC_CHECK_END();
   NEW_RECT(r, x, y, w, h);
   if (!r) return;
   e->damages = eina_list_append(e->damages, r);
   e->changed = EINA_TRUE;
}
