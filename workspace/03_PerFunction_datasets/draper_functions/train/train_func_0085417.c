elm_gengrid_align_set(Evas_Object *obj,
                      double align_x,
                      double align_y)
{
   double old_h, old_y;

   ELM_GENGRID_CHECK(obj);
   ELM_GENGRID_DATA_GET(obj, sd);

   old_h = sd->align_x;
   old_y = sd->align_y;

   if (align_x > 1.0)
     align_x = 1.0;
   else if (align_x < 0.0)
     align_x = 0.0;
   sd->align_x = align_x;

   if (align_y > 1.0)
     align_y = 1.0;
   else if (align_y < 0.0)
     align_y = 0.0;
   sd->align_y = align_y;

   if ((old_h != sd->align_x) || (old_y != sd->align_y))
     evas_object_smart_calculate(sd->pan_obj);
}
