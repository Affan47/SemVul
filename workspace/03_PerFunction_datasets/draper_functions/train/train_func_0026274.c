_ibox_cb_event_border_urgent_change(void *data __UNUSED__, int type __UNUSED__, void *event)
{
   E_Event_Border_Urgent_Change *ev;
   IBox *b;
   IBox_Icon *ic;
   Eina_List *ibox;

   ev = event;

   ibox = _ibox_zone_find(ev->border->zone);
   EINA_LIST_FREE(ibox, b)
     {
        ic = _ibox_icon_find(b, ev->border);
        if (!ic) continue;
        if (ev->border->client.icccm.urgent)
          {
             e_gadcon_urgent_show(b->inst->gcc->gadcon);
             edje_object_signal_emit(ic->o_holder, "e,state,urgent", "e");
             edje_object_signal_emit(ic->o_holder2, "e,state,urgent", "e");
          }
        else
          {
             edje_object_signal_emit(ic->o_holder, "e,state,not_urgent", "e");
             edje_object_signal_emit(ic->o_holder2, "e,state,not_urgent", "e");
          }
     }

   return ECORE_CALLBACK_PASS_ON;
}
