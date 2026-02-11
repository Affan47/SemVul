elm_gengrid_item_tooltip_window_mode_set(Elm_Object_Item *it,
                                         Eina_Bool disable)
{
   ELM_GENGRID_ITEM_CHECK_OR_RETURN(it, EINA_FALSE);

   ((Elm_Gen_Item *)it)->tooltip.free_size = disable;
   if (VIEW(it)) return elm_widget_item_tooltip_window_mode_set(it, disable);

   return EINA_TRUE;
}
