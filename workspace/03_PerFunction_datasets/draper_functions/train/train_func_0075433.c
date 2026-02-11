e_widget_slider_value_double_set(Evas_Object *slider, double dval)
{
   E_Widget_Data *wd;

   wd = e_widget_data_get(slider);
   if (!wd->dval) return 0;
   *(wd->dval) = dval;
   e_slider_value_set(wd->o_slider, dval);
   return 1;
}
