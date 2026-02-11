evry_view_toggle(Evry_State *s, const char *trigger)
{
   Evry_View *view, *v = NULL;
   Eina_List *l, *ll;
   Eina_Bool triggered = FALSE;
   Evry_Window *win = s->selector->win;

   if (trigger)
     {
        EINA_LIST_FOREACH (evry_conf->views, ll, view)
          {
             if (view->trigger && !strncmp(trigger, view->trigger, 1) &&
                 (!s->view || (view->id != s->view->id)) &&
                 (v = view->create(view, s, win->o_main)))
               {
                  triggered = EINA_TRUE;
                  goto found;
               }
          }
     }
   else
     {
        if (s->view)
          l = eina_list_data_find_list(evry_conf->views, s->view->id);
        else
          {
             view = evry_conf->views->data;
             v = view->create(view, s, win->o_main);
             goto found;
          }

        if (l && l->next)
          l = l->next;
        else
          l = evry_conf->views;

        EINA_LIST_FOREACH (l, ll, view)
          {
             if ((!view->trigger) &&
                 ((!s->view || (view->id != s->view->id)) &&
                  (v = view->create(view, s, win->o_main))))
               goto found;
          }
     }

found:
   if (!v) return 0;

   _evry_list_win_show(win);

   if (s->view)
     {
        _evry_view_hide(win, s->view, 0);
        s->view->destroy(s->view);
     }

   s->view = v;
   s->view->state = s;
   _evry_view_show(win, s->view, 0);
   view->update(s->view);

   return triggered;
}
