_view_destroy(Evry_View *ev)
{
   Ecore_Event_Handler *h;

   GET_VIEW(v, ev);

   _view_clear(ev);

   evas_object_del(v->span);
   evas_object_del(v->bg);
   evas_object_del(v->sframe);

   evry_tab_view_free(v->tabs);

   EINA_LIST_FREE (v->handlers, h)
     ecore_event_handler_del(h);

   E_FREE(v);
}
