_ecore_evas_ews_cb_focus_out(void *data, Evas *e __UNUSED__, Evas_Object *obj __UNUSED__, void *event_info __UNUSED__)
{
   Ecore_Evas *ee = data;
   if (ee->deleted) return;
   ecore_evas_focus_set(ee, EINA_FALSE);
}
