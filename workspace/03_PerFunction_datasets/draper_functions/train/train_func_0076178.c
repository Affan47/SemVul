direct_free( const char *file, int line, const char *func, const char *what, void *mem )
{
     unsigned int i;

     if (!mem) {
          D_WARN( "%s (NULL) called", __FUNCTION__ );
          return;
     }

     if (!direct_config->debugmem) {
          D_DEBUG_AT( Direct_Mem, "  - number of bytes of %s [%s:%d in %s()] -> %p\n", what, file, line, func, mem );
          free( mem );
          return;
     }


     pthread_mutex_lock( &alloc_lock );

     for (i=0; i<alloc_count; i++) {
          MemDesc *desc = &alloc_list[i];

          if (desc->mem == mem) {
               free( mem );

               D_DEBUG_AT( Direct_Mem, "  -%6zu bytes [%s:%d in %s()] -> %p '%s'\n",
                           desc->bytes, file, line, func, mem, what );

               if (desc->trace)
                    direct_trace_free_buffer( desc->trace );

               alloc_count--;


               if (i < alloc_count)
                    direct_memmove( desc, desc + 1, (alloc_count - i) * sizeof(MemDesc) );

               pthread_mutex_unlock( &alloc_lock );

               return;
          }
     }

     pthread_mutex_unlock( &alloc_lock );

     D_ERROR( "Direct/Mem: Not freeing unknown %p (%s) from [%s:%d in %s()] - corrupt/incomplete list?\n",
              mem, what, file, line, func );
}
