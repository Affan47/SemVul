elm_table_pack_get(Evas_Object *subobj,
                   int *x,
                   int *y,
                   int *w,
                   int *h)
{
   Evas_Object *obj = elm_widget_parent_widget_get(subobj);
   unsigned short ix, iy, iw, ih;

   ELM_TABLE_CHECK(obj);
   ELM_TABLE_DATA_GET(obj, sd);

   evas_object_table_pack_get
     (ELM_WIDGET_DATA(sd)->resize_obj, subobj, &ix, &iy, &iw, &ih);
   if (x) *x = ix;
   if (y) *y = iy;
   if (w) *w = iw;
   if (h) *h = ih;
}
