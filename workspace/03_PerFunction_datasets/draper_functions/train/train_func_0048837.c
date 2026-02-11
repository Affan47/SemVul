_del_func(void *data, void *obj __UNUSED__)
{
   Instance *inst = data;

   e_gadcon_locked_set(inst->gcc->gadcon, 0);
   e_object_delfn_del(E_OBJECT(inst->win->ewin), inst->del_fn);

   if (inst->hide_animator) ecore_animator_del(inst->hide_animator);
   inst->del_fn = NULL;
   inst->win = NULL;
   edje_object_signal_emit(inst->o_button, "e,state,unfocused", "e");
}
