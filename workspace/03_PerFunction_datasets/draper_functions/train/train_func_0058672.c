elm_multibuttonentry_add(Evas_Object *parent)
{
   Evas_Object *obj;
   Evas *e;
   Widget_Data *wd;

   ELM_WIDGET_STANDARD_SETUP(wd, Widget_Data, parent, e, obj, NULL);

   ELM_SET_WIDTYPE(widtype, "multibuttonentry");
   elm_widget_type_set(obj, "multibuttonentry");
   elm_widget_sub_object_add(parent, obj);
   elm_widget_data_set(obj, wd);

   elm_widget_del_hook_set(obj, _del_hook);
   elm_widget_theme_hook_set(obj, _theme_hook);
   elm_widget_event_hook_set(obj, _event_hook);
   elm_widget_on_focus_hook_set(obj, _on_focus_hook, NULL);
   elm_widget_signal_emit_hook_set(obj, _signal_emit_hook);
   elm_widget_text_set_hook_set(obj, _text_set_hook);
   elm_widget_text_get_hook_set(obj, _text_get_hook);

   wd->base = edje_object_add(e);
   _elm_theme_object_set(obj, wd->base, "multibuttonentry", "base", "default");
   elm_widget_resize_object_set(obj, wd->base);
   elm_widget_can_focus_set(obj, EINA_TRUE);

   wd->view_state = MULTIBUTTONENTRY_VIEW_NONE;
   wd->focused = EINA_FALSE;
   wd->last_btn_select = EINA_TRUE;
   wd->n_str = 0;
   wd->rect_for_end = NULL;
   wd->add_callback = NULL;
   wd->add_callback_data = NULL;
   wd->editable = EINA_TRUE;

   evas_object_smart_callbacks_descriptions_set(obj, _signals);

   _view_init(obj);
   _event_init(obj);

   return obj;
}
