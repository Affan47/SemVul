direct_debug_at( DirectDebugDomain *domain,
                 const char        *format, ... )
{
     bool enabled;

     pthread_mutex_lock( &domains_lock );

     enabled = check_domain( domain );

     pthread_mutex_unlock( &domains_lock );

     if (enabled) {
          va_list ap;

          va_start( ap, format );

          debug_domain_vprintf( domain->name, domain->name_len, format, ap );

          va_end( ap );
     }
}
