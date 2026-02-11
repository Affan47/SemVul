_elm_icon_smart_add(Evas_Object *obj)
{
   EVAS_SMART_DATA_ALLOC(obj, Elm_Icon_Smart_Data);

   ELM_WIDGET_CLASS(_elm_icon_parent_sc)->base.add(obj);

   priv->lookup_order = ELM_ICON_LOOKUP_THEME_FDO;

#ifdef HAVE_ELEMENTARY_ETHUMB
   priv->thumb.request = NULL;
#endif
}
