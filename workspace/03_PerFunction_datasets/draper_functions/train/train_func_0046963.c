_ecore_evas_ews_hide(Ecore_Evas *ee)
{
   ee->should_be_visible = EINA_FALSE;
   evas_object_hide(ee->engine.ews.image);

   if (ee->func.fn_hide) ee->func.fn_hide(ee);
   _ecore_evas_ews_event(ee, ECORE_EVAS_EWS_EVENT_HIDE);
}
