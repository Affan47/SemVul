elm_naviframe_bottom_item_get(const Evas_Object *obj)
{
   ELM_NAVIFRAME_CHECK(obj) NULL;
   ELM_NAVIFRAME_DATA_GET(obj, sd);

   if (!sd->stack) return NULL;
   return (Elm_Object_Item *)(EINA_INLIST_CONTAINER_GET
                                (sd->stack, Elm_Naviframe_Item));
}
