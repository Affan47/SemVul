elm_widget_show_region_get(const Evas_Object *obj,
                           Evas_Coord        *x,
                           Evas_Coord        *y,
                           Evas_Coord        *w,
                           Evas_Coord        *h)
{
   API_ENTRY return;
   if (x) *x = sd->rx;
   if (y) *y = sd->ry;
   if (w) *w = sd->rw;
   if (h) *h = sd->rh;
}
