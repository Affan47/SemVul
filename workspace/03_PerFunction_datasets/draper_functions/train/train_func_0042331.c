_select_button(Evas_Object *obj, Evas_Object *btn)
{
   Widget_Data *wd = elm_widget_data_get(obj);

   if (!wd) return;
   if (btn)
     {
        _change_current_button(obj, btn);
        if (elm_widget_focus_get(obj))
          {
             elm_object_focus_set(wd->entry, EINA_FALSE);
             evas_object_focus_set(btn, EINA_TRUE);
          }
     }
   else
     {
        _change_current_button_state(obj, MULTIBUTTONENTRY_BUTTON_STATE_DEFAULT);
        if (elm_widget_focus_get(obj) && wd->editable)
          elm_object_focus_set(wd->entry, EINA_TRUE);
     }
}
