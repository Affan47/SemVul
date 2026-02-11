_e_fm_main_udisks_volume_del(const char *udi)
{
   E_Volume *v;

   v = e_volume_find(udi);
   if (!v) return;
   if (v->guard)
     {
        ecore_timer_del(v->guard);
        v->guard = NULL;
     }
   if (v->validated)
     {
        INF("--VOL %s", v->udi);

           ecore_ipc_server_send(_e_fm_ipc_server,
                                 6 ,
                                 E_FM_OP_VOLUME_DEL,
                                 0, 0, 0, v->udi, eina_stringshare_strlen(v->udi) + 1);
     }
   v->optype = E_VOLUME_OP_TYPE_NONE;
   if (v->storage && v->storage->requires_eject) return;


   if (v->prop_handler) e_dbus_signal_handler_del(_e_fm_main_udisks_conn, v->prop_handler);
   _e_vols = eina_list_remove(_e_vols, v);
   _e_fm_shared_device_volume_free(v);
}
