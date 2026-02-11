_gc_init(E_Gadcon *gc, const char *name, const char *id, const char *style)
{
   Evas_Object *o;
   E_Gadcon_Client *gcc;
   Config_Face *inst;

   inst = eina_hash_find(temperature_config->faces, id);
   if (!inst)
     {
        inst = E_NEW(Config_Face, 1);
        inst->id = eina_stringshare_add(id);
        inst->poll_interval = 128;
        inst->low = 30;
        inst->high = 80;
        inst->sensor_type = SENSOR_TYPE_NONE;
        inst->sensor_name = NULL;
        inst->units = CELCIUS;
#ifdef HAVE_EEZE
        inst->backend = UDEV;
#endif
        if (!temperature_config->faces)
          temperature_config->faces = eina_hash_string_superfast_new(NULL);
        eina_hash_direct_add(temperature_config->faces, inst->id, inst);
     }
   if (!inst->id) inst->id = eina_stringshare_add(id);
   E_CONFIG_LIMIT(inst->poll_interval, 1, 1024);
   E_CONFIG_LIMIT(inst->low, 0, 100);
   E_CONFIG_LIMIT(inst->high, 0, 220);
   E_CONFIG_LIMIT(inst->units, CELCIUS, FAHRENHEIT);
#ifdef HAVE_EEZE
   E_CONFIG_LIMIT(inst->backend, TEMPGET, UDEV);
#endif

   o = edje_object_add(gc->evas);
   e_theme_edje_object_set(o, "base/theme/modules/temperature",
			   "e/modules/temperature/main");

   gcc = e_gadcon_client_new(gc, name, id, style, o);
   gcc->data = inst;

   inst->gcc = gcc;
   inst->o_temp = o;
   inst->module = temperature_config->module;
   inst->have_temp = -1;
#ifdef HAVE_EEZE
   if (inst->backend == TEMPGET)
     {
        inst->tempget_data_handler =
          ecore_event_handler_add(ECORE_EXE_EVENT_DATA,
				  _temperature_cb_exe_data, inst);
        inst->tempget_del_handler =
          ecore_event_handler_add(ECORE_EXE_EVENT_DEL,
				  _temperature_cb_exe_del, inst);
     }
   else
     {
        eeze_init();
        inst->temp_poller =
	  ecore_poller_add(ECORE_POLLER_CORE, inst->poll_interval,
			   temperature_udev_update_poll, inst);
        temperature_udev_update(inst);
     }
#else
   inst->tempget_data_handler =
     ecore_event_handler_add(ECORE_EXE_EVENT_DATA,
			     _temperature_cb_exe_data, inst);
   inst->tempget_del_handler =
     ecore_event_handler_add(ECORE_EXE_EVENT_DEL,
			     _temperature_cb_exe_del, inst);
#endif

   temperature_face_update_config(inst);

   evas_object_event_callback_add(o, EVAS_CALLBACK_MOUSE_DOWN,
				  _temperature_face_cb_mouse_down, inst);
   return gcc;
}
