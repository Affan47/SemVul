_box_button_cb_dnd_enter(void *data __UNUSED__, const char *type, void *event)
{
   E_Event_Dnd_Enter *ev = event;

   if (strcmp(type, "text/uri-list") && strcmp(type, "XdndDirectSave0")) return;
   e_drop_handler_action_set(ev->action);
}
