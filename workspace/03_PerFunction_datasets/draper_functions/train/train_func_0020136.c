_pan_child_size_get(Evas_Object *obj, Evas_Coord *w, Evas_Coord *h)
{
   Smart_Data *sd = evas_object_smart_data_get(obj);
   if (w) *w = sd->cw;
   if (h) *h = sd->ch;
}
