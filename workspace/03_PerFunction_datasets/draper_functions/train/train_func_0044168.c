pulse_shutdown(void)
{
   if ((!pulse_init_count) || (!--pulse_init_count)) return;

   if (pulse_sinks) eina_hash_free(pulse_sinks);
   if (pulse_sources) eina_hash_free(pulse_sources);
   pulse_sinks = pulse_sources = NULL;
   eina_log_domain_unregister(pa_log_dom);
   ecore_con_shutdown();
   ecore_shutdown();
   eina_shutdown();
}
