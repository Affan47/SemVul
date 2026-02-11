_battery_cb_exe_data(void *data __UNUSED__, int type __UNUSED__, void *event)
{
   Ecore_Exe_Event_Data *ev;
   Instance *inst;
   Eina_List *l;
   int i;

   ev = event;
   if (ev->exe != battery_config->batget_exe) return ECORE_CALLBACK_PASS_ON;
   if ((ev->lines) && (ev->lines[0].line))
     {
        for (i = 0; ev->lines[i].line; i++)
          {
             if (!strcmp(ev->lines[i].line, "ERROR"))
               EINA_LIST_FOREACH(battery_config->instances, l, inst)
                 {
                    edje_object_signal_emit(inst->o_battery,
                                            "e,state,unknown", "e");
                    edje_object_part_text_set(inst->o_battery,
                                              "e.text.reading", _("ERROR"));
                    edje_object_part_text_set(inst->o_battery,
                                              "e.text.time", _("ERROR"));

                    if (inst->popup_battery)
                      {
                         edje_object_signal_emit(inst->popup_battery,
                                                 "e,state,unknown", "e");
                         edje_object_part_text_set(inst->popup_battery,
                                                   "e.text.reading", _("ERROR"));
                         edje_object_part_text_set(inst->popup_battery,
                                                   "e.text.time", _("ERROR"));
                      }
                 }
             else
               {
                  int full = 0;
                  int time_left = 0;
                  int time_full = 0;
                  int have_battery = 0;
                  int have_power = 0;

                  if (sscanf(ev->lines[i].line, "%i %i %i %i %i", &full, &time_left, &time_full,
                             &have_battery, &have_power) == 5)
                    _battery_update(full, time_left, time_full,
                                    have_battery, have_power);
                  else
                    e_powersave_mode_set(E_POWERSAVE_MODE_LOW);
               }
          }
     }
   return ECORE_CALLBACK_DONE;
}
