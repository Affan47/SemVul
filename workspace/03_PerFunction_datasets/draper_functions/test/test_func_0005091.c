_gc_shutdown(E_Gadcon_Client *gcc)
{
   Instance *inst;

#ifdef HAVE_EEZE
   eeze_shutdown();
#elif !defined __OpenBSD__
   e_hal_shutdown();
   e_dbus_shutdown();
#endif

   inst = gcc->data;
   if (battery_config)
     battery_config->instances =
       eina_list_remove(battery_config->instances, inst);
   evas_object_del(inst->o_battery);
   if (inst->warning)
     {
        e_object_del(E_OBJECT(inst->warning));
        inst->popup_battery = NULL;
     }
   E_FREE(inst);
}
