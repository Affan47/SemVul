_e_wid_focus_hook(Evas_Object *obj)
{
   E_Widget_Data *wd;

   wd = e_widget_data_get(obj);
   if (e_widget_focus_get(obj))
     {
        edje_object_signal_emit(e_scrollframe_edje_object_get(wd->o_scrollframe), "e,state,focused", "e");
        if (wd->o_fobj) evas_object_focus_set(wd->o_fobj, 1);
        else evas_object_focus_set(wd->o_scrollframe, 1);
     }
   else
     {
        edje_object_signal_emit(e_scrollframe_edje_object_get(wd->o_scrollframe), "e,state,unfocused", "e");
        if (wd->o_fobj) evas_object_focus_set(wd->o_fobj, 0);
        evas_object_focus_set(wd->o_scrollframe, 0);
     }
}
