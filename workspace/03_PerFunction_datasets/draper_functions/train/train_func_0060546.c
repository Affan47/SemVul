_elm_ews_border_fullscreen_apply(Ecore_Evas *ee, Evas_Object *o)
{
   const char *sig;
   if (ecore_evas_fullscreen_get(ee))
     sig = "elm,state,fullscreen,on";
   else
     sig = "elm,state,fullscreen,off";
   edje_object_signal_emit(o, sig, "elm");
   _elm_ews_border_geo_apply(ee, o);
}
