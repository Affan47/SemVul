_elm_ews_wm_border_del(void *data)
{
   Evas_Object *deco = data;
   evas_object_del(deco);

   if (_ews_border_mover_obj == deco)
     {
        if (_ews_border_mover)
          {
             ecore_animator_del(_ews_border_mover);
             _ews_border_mover = NULL;
          }
        _ews_border_mover_obj = NULL;
     }
}
