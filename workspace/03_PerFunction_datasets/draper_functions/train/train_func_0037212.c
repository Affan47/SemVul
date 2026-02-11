_elm_widget_item_disabled_set(Elm_Widget_Item *item, Eina_Bool disabled)
{
   ELM_WIDGET_ITEM_CHECK_OR_RETURN(item);

   if (item->disabled == disabled) return;
   item->disabled = !!disabled;
   if (item->disable_func) item->disable_func(item);
}
