_e_mod_comp_win_restack(E_Comp_Win *cw)
{
   Eina_Inlist *prev, *next;
   Eina_List *l;
   E_Comp_Win *cwp = NULL, *cwn = NULL;

   next = EINA_INLIST_GET(cw)->next;
   if (next) cwn = EINA_INLIST_CONTAINER_GET(next, E_Comp_Win);
   prev = EINA_INLIST_GET(cw)->prev;
   if (prev) cwp = EINA_INLIST_CONTAINER_GET(prev, E_Comp_Win);

   if (cwp)
     e_layout_child_raise_above(cw->shobj, cwp->shobj);
   else if (cwn)
     e_layout_child_raise_above(cw->shobj, cwn->shobj);
   if (cw->bd)
     {
        E_Border *tmp;

        EINA_LIST_FOREACH(cw->bd->client.e.state.video_child, l, tmp)
          {
             E_Comp_Win *tcw;

             tcw = eina_hash_find(borders,
                                  e_util_winid_str_get(tmp->client.win));
             if (!tcw) continue;
             e_layout_child_lower_below(tcw->shobj, cw->shobj);
          }
     }
}
