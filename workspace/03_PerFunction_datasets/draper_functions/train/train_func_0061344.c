init_fallback_log( void )
{
     fallback_log.type = DLT_STDERR;
     fallback_log.fd   = fileno( stderr );

     direct_util_recursive_pthread_mutex_init( &fallback_log.lock );

     D_MAGIC_SET( &fallback_log, DirectLog );
}
