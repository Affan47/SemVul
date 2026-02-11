_ecore_evas_pre_free(Ecore_Evas *ee)
{
   Evas_Object *obj = _ecore_evas_associate_get(ee);
   if (!obj)
     return;
   _ecore_evas_object_dissociate(ee, obj);
   evas_object_del(obj);
}
