e_widget_ilist_freeze(Evas_Object *obj)
{
   E_Widget_Data *wd;

   wd = e_widget_data_get(obj);
   if (!wd) return;
   e_ilist_freeze(wd->o_ilist);
}
