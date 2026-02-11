direct_print_interface_leaks( void )
{
     unsigned int i;

     pthread_mutex_lock( &alloc_lock );

     if (alloc_count ) {
          direct_log_printf( NULL, "Interface instances remaining (%d): \n", alloc_count );

          for (i=0; i<alloc_count; i++) {
               InterfaceDesc *desc = &alloc_list[i];

               direct_log_printf( NULL, "  - '%s' at %p (%s) allocated in %s (%s: %u)\n", desc->name,
                        desc->interface, desc->what, desc->func, desc->file, desc->line );

               if (desc->trace)
                    direct_trace_print_stack( desc->trace );
          }
     }

     pthread_mutex_unlock( &alloc_lock );
}
