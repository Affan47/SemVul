_elm_progressbar_smart_del(Evas_Object *obj)
{
   ELM_PROGRESSBAR_DATA_GET(obj, sd);

   if (sd->units) eina_stringshare_del(sd->units);

   ELM_WIDGET_CLASS(_elm_progressbar_parent_sc)->base.del(obj);
}
