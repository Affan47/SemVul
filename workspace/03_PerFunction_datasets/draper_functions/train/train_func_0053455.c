_elm_widget_item_signal_emit(Elm_Widget_Item *item,
                             const char *emission,
                             const char *source)
{
   ELM_WIDGET_ITEM_CHECK_OR_RETURN(item);
   if (item->signal_emit_func)
     item->signal_emit_func((Elm_Object_Item *)item, emission, source);
}
