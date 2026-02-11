_systray_cb_reparent_notify(void *data, int type __UNUSED__, void *event)
{
   Ecore_X_Event_Window_Reparent *ev = event;
   Instance *inst = data;
   Icon *icon;
   Eina_List *l;

   EINA_LIST_FOREACH(inst->icons, l, icon)
     if ((icon->win == ev->win) && (ev->parent != inst->win.base))
       {
          _systray_icon_del_list(inst, l, icon);
          break;
       }

   return ECORE_CALLBACK_PASS_ON;
}
