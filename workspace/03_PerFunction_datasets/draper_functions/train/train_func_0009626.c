_policy_border_add(E_Border *bd)
{
   if (!bd) return;


   ecore_x_e_illume_zone_set(bd->client.win, bd->zone->black_win);


   if (bd->stolen) return;


   if ((bd->fullscreen) || (bd->need_fullscreen))
     {
        E_Border *ind, *sft;


        if ((ind = e_illume_border_indicator_get(bd->zone)))
          {

	     if (ind->visible) e_illume_border_hide(ind);
          }

        if ((sft = e_illume_border_softkey_get(bd->zone)))
          {
             if (e_illume_border_is_conformant(bd))
               {
                  if (sft->visible) e_illume_border_hide(sft);
               }
             else
               {
                  if (!sft->visible) e_illume_border_show(sft);
               }
          }
     }


   if ((bd->client.icccm.accepts_focus) || (bd->client.icccm.take_focus))
     _pol_focus_stack = eina_list_append(_pol_focus_stack, bd);

   if ((e_illume_border_is_softkey(bd)) || (e_illume_border_is_indicator(bd)))
     _policy_zone_layout_update(bd->zone);
   else
     {

	_policy_border_set_focus(bd);
     }
}
