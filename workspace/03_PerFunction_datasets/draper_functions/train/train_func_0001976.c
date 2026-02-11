_ibox_cb_event_desk_show(void *data __UNUSED__, int type __UNUSED__, void *event)
{
   E_Event_Desk_Show *ev;
   IBox *b;
   Eina_List *ibox;

   ev = event;

   ibox = _ibox_zone_find(ev->desk->zone);
   EINA_LIST_FREE(ibox, b)
     {
        if (b->inst->ci->show_desk)
          {
             _ibox_empty(b);
             _ibox_fill(b);
             _ibox_resize_handle(b);
             _gc_orient(b->inst->gcc, -1);
          }
     }

   return ECORE_CALLBACK_PASS_ON;
}
