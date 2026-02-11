_gc_init(E_Gadcon *gc, const char *name, const char *id, const char *style)
{
   Evas_Object *o;
   E_Gadcon_Client *gcc;
   Instance *inst;
   char todaystr[128];

   inst = E_NEW(Instance, 1);
   inst->cfg = _conf_item_get(id);

   _todaystr_eval(inst, todaystr, sizeof(todaystr) - 1);

   o = edje_object_add(gc->evas);
   edje_object_signal_callback_add(o, "e,state,sizing,changed", "*",
                                   _clock_sizing_changed_cb, inst);
   if (inst->cfg->digital_clock)
     e_theme_edje_object_set(o, "base/theme/modules/clock",
                             "e/modules/clock/digital");
   else
     e_theme_edje_object_set(o, "base/theme/modules/clock",
                             "e/modules/clock/main");
   if (inst->cfg->show_date)
     edje_object_signal_emit(o, "e,state,date,on", "e");
   else
     edje_object_signal_emit(o, "e,state,date,off", "e");
   if (inst->cfg->digital_24h)
     edje_object_signal_emit(o, "e,state,24h,on", "e");
   else
     edje_object_signal_emit(o, "e,state,24h,off", "e");
   if (inst->cfg->show_seconds)
     edje_object_signal_emit(o, "e,state,seconds,on", "e");
   else
     edje_object_signal_emit(o, "e,state,seconds,off", "e");

   edje_object_part_text_set(o, "e.text.today", todaystr);
   edje_object_message_signal_process(o);
   evas_object_show(o);

   gcc = e_gadcon_client_new(gc, name, id, style, o);
   gcc->data = inst;

   inst->gcc = gcc;
   inst->o_clock = o;

   evas_object_event_callback_add(inst->o_clock,
                                  EVAS_CALLBACK_MOUSE_DOWN,
                                  _clock_cb_mouse_down,
                                  inst);

   clock_instances = eina_list_append(clock_instances, inst);

   if (!update_today) _update_today_timer(NULL);

   return gcc;
}
