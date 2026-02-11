_elm_smart_pan_gravity_get(Evas_Object *obj, double *x, double *y)
{
   API_ENTRY return;
   if (x) *x = sd->gravity_x;
   if (y) *y = sd->gravity_y;
}
