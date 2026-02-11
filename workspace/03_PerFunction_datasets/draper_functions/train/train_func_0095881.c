_systray_cb_window_configure(void *data, int type __UNUSED__, void *event)
{
   Ecore_X_Event_Window_Configure *ev = event;
   Instance *inst = data;
   Icon *icon;
   const Eina_List *l;

   EINA_LIST_FOREACH(inst->icons, l, icon)
     if (icon->win == ev->win)
       {
          _systray_icon_geometry_apply(icon);
          break;
       }

   return ECORE_CALLBACK_PASS_ON;
}
