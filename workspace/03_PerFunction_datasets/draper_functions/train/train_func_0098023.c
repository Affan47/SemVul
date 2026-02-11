_e_mod_quickpanel_cb_mouse_up(void *data, int type __UNUSED__, void *event)
{
   Ecore_Event_Mouse_Button *ev;
   E_Illume_Quickpanel *qp;

   ev = event;
   if (!(qp = data)) return ECORE_CALLBACK_PASS_ON;
   if (ev->event_window != qp->clickwin) return ECORE_CALLBACK_PASS_ON;
   if (qp->visible) e_mod_quickpanel_hide(qp);
   return ECORE_CALLBACK_PASS_ON;
}
