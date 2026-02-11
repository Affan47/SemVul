e_fm2_device_storage_add(E_Storage *s)
{
   Eina_List *l;
   E_Volume *v;

   if (e_fm2_device_storage_find(s->udi)) return;

   s->validated = EINA_TRUE;
   _e_stores = eina_list_append(_e_stores, s);


   if ((s->removable == 0) &&
       (s->media_available == 0) &&
       (s->media_size == 0) &&
       (s->requires_eject == 0) &&
       (s->hotpluggable == 0) &&
       (s->media_check_enabled == 0))
     {

     }
   else
     {
        s->trackable = EINA_TRUE;
     }

   EINA_LIST_FOREACH(_e_vols, l, v)
     {
        if ((!v->storage) && (s->udi == v->parent))
          {
             v->storage = s;
             _e_fm2_device_volume_setup(v);
          }
     }
}
