_policy_border_show_below(E_Border *bd)
{
   Eina_List *l;
   E_Border *prev;
   int pos = 0, layer = 0, i;


   if (!bd) return;

   if (bd->client.icccm.transient_for)
     {
        if ((prev = e_border_find_by_client_window(bd->client.icccm.transient_for)))
          {
             _policy_border_set_focus(prev);
             return;
          }
     }


   layer = bd->layer;
   if (layer < 0) layer = 0;
   pos = 1 + (layer / 50);
   if (pos > 10) pos = 10;


   for (i = (pos + 1); i < 11; i++)
     {
        E_Border *b;

        EINA_LIST_REVERSE_FOREACH(bd->zone->container->layers[i].clients, l, b)
          {

             if (b == bd) continue;


             if (b->zone != bd->zone) continue;


             if (e_illume_border_is_indicator(b)) continue;
             if (e_illume_border_is_softkey(b)) continue;
             if (e_illume_border_is_keyboard(b)) continue;
             if (e_illume_border_is_quickpanel(b)) continue;
             if (e_illume_border_is_home(b)) continue;

             if ((bd->fullscreen) || (bd->need_fullscreen))
               {
                  _policy_border_set_focus(b);
                  return;
               }
             else
               {

                  if (E_CONTAINS(bd->x, bd->y, bd->w, bd->h,
                                 b->x, b->y, b->w, b->h))
                    {
                       _policy_border_set_focus(b);
                       return;
                    }
               }
          }
     }


   EINA_LIST_REVERSE_FOREACH(_pol_focus_stack, l, prev)
     {
        if (prev->zone != bd->zone) continue;
        _policy_border_set_focus(prev);
        return;
     }


   _policy_focus_home(bd->zone);
}
