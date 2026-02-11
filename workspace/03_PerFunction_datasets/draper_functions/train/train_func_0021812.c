_pager_cb_event_border_icon_change(void *data __UNUSED__, int type __UNUSED__, void *event)
{
   E_Event_Border_Icon_Change *ev = event;
   Eina_List *l;
   Pager *p;

   EINA_LIST_FOREACH(pagers, l, p)
     {
        Eina_List *l2;
        Pager_Desk *pd;

        if (p->zone != ev->border->zone) continue;
        EINA_LIST_FOREACH(p->desks, l2, pd)
          {
             Pager_Win *pw;

             pw = _pager_desk_window_find(pd, ev->border);
             if (pw)
               {
                  Evas_Object *o;

                  if (pw->o_icon)
                    {
                       evas_object_del(pw->o_icon);
                       pw->o_icon = NULL;
                    }
                  o = e_border_icon_add(ev->border,
                                        evas_object_evas_get(p->o_table));
                  if (o)
                    {
                       pw->o_icon = o;
                       evas_object_show(o);
                       edje_object_part_swallow(pw->o_window,
                                                "e.swallow.icon", o);
                    }
               }
          }
     }

   return ECORE_CALLBACK_PASS_ON;
}
