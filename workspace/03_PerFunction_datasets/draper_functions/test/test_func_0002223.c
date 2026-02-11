_e_pointer_free(E_Pointer *p)
{
   if (!p) return;
   _e_pointers = eina_list_remove(_e_pointers, p);

   _e_pointer_canvas_del(p);

   E_FREE_LIST(p->stack, _e_pointer_stack_free);

   if (p->type) eina_stringshare_del(p->type);
   if (p->idle_timer) ecore_timer_del(p->idle_timer);
   if (p->idle_poller) ecore_poller_del(p->idle_poller);

   p->type = NULL;
   p->idle_timer = NULL;
   p->idle_poller = NULL;
   E_FREE(p);
}
