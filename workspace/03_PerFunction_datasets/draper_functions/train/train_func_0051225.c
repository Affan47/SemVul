ecore_event_handler_data_set(Ecore_Event_Handler *eh,
                             const void          *data)
{
   void *old = NULL;

   EINA_MAIN_LOOP_CHECK_RETURN_VAL(NULL);
   _ecore_lock();
   if (!ECORE_MAGIC_CHECK(eh, ECORE_MAGIC_EVENT_HANDLER))
     {
        ECORE_MAGIC_FAIL(eh, ECORE_MAGIC_EVENT_HANDLER, "ecore_event_handler_data_set");
        goto unlock;
     }
   old = eh->data;
   eh->data = (void *)data;
unlock:
   _ecore_unlock();

   return old;
}
