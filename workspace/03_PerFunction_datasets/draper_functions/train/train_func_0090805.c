elm_object_signal_callback_add(Evas_Object *obj, const char *emission, const char *source, Edje_Signal_Cb func, void *data)
{
    EINA_SAFETY_ON_NULL_RETURN(obj);
    EINA_SAFETY_ON_NULL_RETURN(func);
    elm_widget_signal_callback_add(obj, emission, source, func, data);
}
