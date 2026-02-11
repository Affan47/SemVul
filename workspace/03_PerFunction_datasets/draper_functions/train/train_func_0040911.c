_dismissed(void *data __UNUSED__, Evas_Object *obj, void *event_info __UNUSED__)
{
   Evas_Object *ctxpopup_data = evas_object_data_get(obj, "im");
   if (ctxpopup_data) evas_object_del(ctxpopup_data);
   evas_object_del(obj);
}
