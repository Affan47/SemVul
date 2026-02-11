_battery_warning_popup_destroy(Instance *inst)
{
   if (battery_config->alert_timer)
     {
        ecore_timer_del(battery_config->alert_timer);
        battery_config->alert_timer = NULL;
     }
   if ((!inst) || (!inst->warning)) return;
   e_object_del(E_OBJECT(inst->warning));
   inst->warning = NULL;
   inst->popup_battery = NULL;
}
