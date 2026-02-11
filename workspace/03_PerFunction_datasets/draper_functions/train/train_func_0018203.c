elm_layout_edje_object_can_access_get(Evas_Object *obj)
{
   ELM_LAYOUT_CHECK(obj) EINA_FALSE;
   ELM_LAYOUT_DATA_GET_OR_RETURN_VAL(obj, sd, EINA_FALSE);

   return ELM_WIDGET_DATA(sd)->can_access;
}
