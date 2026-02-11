e_smart_monitor_crtc_set(Evas_Object *obj, E_Randr_Crtc_Info *crtc)
{
   E_Smart_Data *sd;


   if (!(sd = evas_object_smart_data_get(obj))) return;


   sd->crtc = crtc;
}
