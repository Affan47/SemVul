_clock_popup_desk_change(Instance *inst, int type __UNUSED__, E_Event_Desk_After_Show *ev)
{
   if (!inst->gcc->gadcon || !inst->gcc->gadcon->shelf) return ECORE_CALLBACK_RENEW;
   if (e_shelf_desk_visible(inst->gcc->gadcon->shelf, ev->desk)) return ECORE_CALLBACK_RENEW;
   _clock_popup_free(inst);
   return ECORE_CALLBACK_RENEW;
}
