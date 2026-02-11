_pager_cb_event_border_stack(void *data __UNUSED__, int type __UNUSED__, void *event)
{
   E_Event_Border_Stack *ev = event;
   Eina_List *l;
   Pager *p;

   EINA_LIST_FOREACH(pagers, l, p)
     {
        Eina_List *l2;
        Pager_Desk *pd;

        if (p->zone != ev->border->zone) continue;
        EINA_LIST_FOREACH(p->desks, l2, pd)
          {
             Pager_Win *pw, *pw2 = NULL;

             pw = _pager_desk_window_find(pd, ev->border);
             if (pw)
               {
                  E_Border *bd;

                  bd = e_util_desk_border_below(ev->border);
                  if (bd) pw2 = _pager_desk_window_find(pd, bd);
                  if (pw2)
                    {
                       e_layout_child_raise_above(pw->o_window, pw2->o_window);
                       continue;
                    }
                  bd = e_util_desk_border_above(ev->border);
                  if (bd) pw2 = _pager_desk_window_find(pd, bd);
                  if (pw2)
                    {
                       e_layout_child_lower_below(pw->o_window, pw2->o_window);
                       continue;
                    }
               }
          }
     }

   return ECORE_CALLBACK_PASS_ON;
}
