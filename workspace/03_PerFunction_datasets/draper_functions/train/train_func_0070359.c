ecore_poller_del(Ecore_Poller *poller)
{
   void *data;

   EINA_MAIN_LOOP_CHECK_RETURN_VAL(NULL);
   if (!ECORE_MAGIC_CHECK(poller, ECORE_MAGIC_POLLER))
     {
        ECORE_MAGIC_FAIL(poller, ECORE_MAGIC_POLLER,
                         "ecore_poller_del");
        return NULL;
     }


   if (poller_walking > 0)
     {
        poller_delete_count++;
        poller->delete_me = 1;
        return poller->data;
     }

   data = poller->data;
   pollers[poller->ibit] = (Ecore_Poller *)eina_inlist_remove(EINA_INLIST_GET(pollers[poller->ibit]), EINA_INLIST_GET(poller));
   ecore_poller_mp_free(poller);
   _ecore_poller_next_tick_eval();
   return data;
}
