_gc_init(E_Gadcon *gc, const char *gcname, const char *id, const char *style)
{
   Instance *inst;


   inst = E_NEW(Instance, 1);

   inst->o_xkbswitch = edje_object_add(gc->evas);
   inst->layout = e_xkb_layout_get();
   if (e_config->xkb.only_label)
     e_theme_edje_object_set(inst->o_xkbswitch,
                             "base/theme/modules/xkbswitch",
                             "e/modules/xkbswitch/noflag");
   else
     e_theme_edje_object_set(inst->o_xkbswitch,
                             "base/theme/modules/xkbswitch",
                             "e/modules/xkbswitch/main");
   edje_object_part_text_set(inst->o_xkbswitch, "e.text.label",
                             e_xkb_layout_name_reduce(inst->layout->name));

   inst->gcc = e_gadcon_client_new(gc, gcname, id, style, inst->o_xkbswitch);
   inst->gcc->data = inst;

   if (!e_config->xkb.only_label)
     {
        inst->o_xkbflag = e_icon_add(gc->evas);
        e_xkb_e_icon_flag_setup(inst->o_xkbflag, inst->layout->name);

        edje_object_part_swallow(inst->o_xkbswitch, "e.swallow.flag",
                                 inst->o_xkbflag);
     }
   else inst->o_xkbflag = NULL;


   evas_object_event_callback_add(inst->o_xkbswitch, EVAS_CALLBACK_MOUSE_DOWN,
                                  _e_xkb_cb_mouse_down, inst);

   instances = eina_list_append(instances, inst);

   return inst->gcc;
}
