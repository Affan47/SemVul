_pager_desk_cb_drag_finished(E_Drag *drag, int dropped)
{
   Pager_Desk *pd;
   Pager_Desk *pd2 = NULL;
   Eina_List *l;
   E_Desk *desk;
   E_Zone *zone;
   Pager *p;

   pd = drag->data;
   if (!pd) return;
   if (!dropped)
     {

        if (!pd->desk) return;
        zone = e_util_zone_current_get(e_manager_current_get());
        desk = e_desk_current_get(zone);
        EINA_LIST_FOREACH(pagers, l, p)
          {
             pd2 = _pager_desk_find(p, desk);
             if (pd2) break;
          }
        _pager_desk_switch(pd, pd2);
     }
   if (pd->drag.from_pager)
     {
        pd->drag.from_pager->dragging = 0;
        pd->drag.from_pager->just_dragged = 0;
     }
   pd->drag.from_pager = NULL;

   if (act_popup)
     {
        e_grabinput_get(input_window, 0, input_window);
        if (!hold_count) _pager_popup_hide(1);
     }
}
