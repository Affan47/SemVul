_pager_desk_select(Pager_Desk *pd)
{
   Eina_List *l;
   Pager_Desk *pd2;

   if (pd->current) return;

   EINA_LIST_FOREACH(pd->pager->desks, l, pd2)
     {
        if (pd == pd2)
          {
             pd2->current = 1;
             evas_object_raise(pd2->o_desk);
             edje_object_signal_emit(pd2->o_desk, "e,state,selected", "e");
          }
        else
          {
             if (pd2->current)
               {
                  pd2->current = 0;
                  edje_object_signal_emit(pd2->o_desk, "e,state,unselected", "e");
               }
          }
     }
}
