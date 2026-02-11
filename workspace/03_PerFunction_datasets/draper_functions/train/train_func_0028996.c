_box_button_cb_dnd_leave(void *data, const char *type __UNUSED__, void *event __UNUSED__)
{
   Instance *inst = data;

   if (!inst->dnd_obj) return;
   edje_object_signal_emit(inst->dnd_obj, "e,state,default", "e");
   inst->dnd_obj = NULL;
   if (inst->sel_ni) edje_object_signal_emit(inst->sel_ni->o, "e,state,selected", "e");
}
