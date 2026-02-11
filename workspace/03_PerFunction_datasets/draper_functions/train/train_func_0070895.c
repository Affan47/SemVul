_evry_view_key_press(Evry_State *s, Ecore_Event_Key *ev)
{
   if (!s || !s->view || !s->view->cb_key_down) return 0;

   return s->view->cb_key_down(s->view, ev);
}
