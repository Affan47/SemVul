_e_fm_main_hal_storage_del(const char *udi)
{
   E_Storage *s;

   s = e_storage_find(udi);
   if (!s) return;
   if (s->validated)
     {

          ecore_ipc_server_send(_e_fm_ipc_server,
                                6 ,
                                E_FM_OP_STORAGE_DEL,
                                0, 0, 0, s->udi, strlen(s->udi) + 1);
     }
   _e_stores = eina_list_remove(_e_stores, s);
   _e_fm_shared_device_storage_free(s);
}
