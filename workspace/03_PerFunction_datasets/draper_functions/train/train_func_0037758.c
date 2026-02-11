eina_log_domain_registered_level_get(int domain)
{
#ifdef EINA_ENABLE_LOG
   EINA_SAFETY_ON_FALSE_RETURN_VAL(domain >= 0, EINA_LOG_LEVEL_UNKNOWN);
   EINA_SAFETY_ON_FALSE_RETURN_VAL((unsigned int)domain < _log_domains_count,
                                   EINA_LOG_LEVEL_UNKNOWN);
   EINA_SAFETY_ON_TRUE_RETURN_VAL(_log_domains[domain].deleted,
                                  EINA_LOG_LEVEL_UNKNOWN);
   return _log_domains[domain].level;
#else
   (void) domain;
   return 0;
#endif
}
