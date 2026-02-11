te_get_alphanumeric_key(te_event_t anEvent)
{
   char* res = NULL;

   DENTER(EVENT_LAYER, "te_get_alphanumeric_key");

   SGE_ASSERT(NULL != anEvent);

   res = (anEvent->str_key != NULL) ? strdup(anEvent->str_key) : NULL;

   DRETURN(res);
}
