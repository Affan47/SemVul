direct_realloc( const char *file, int line, const char *func, const char *what, void *mem, size_t bytes )
{
     int i;

     if (!mem)
          return direct_malloc( file, line, func, bytes );

     if (!bytes) {
          direct_free( file, line, func, what, mem );
          return NULL;
     }

     if (!direct_config->debugmem) {
          D_DEBUG_AT( Direct_Mem, "  *%6zu bytes [%s:%d in %s()] '%s'\n", bytes, file, line, func, what );
          return realloc( mem, bytes );
     }


     pthread_mutex_lock( &alloc_lock );

     for (i=0; i<alloc_count; i++) {
          MemDesc *desc = &alloc_list[i];

          if (desc->mem == mem) {
               void *new_mem = realloc( mem, bytes );

               D_DEBUG_AT( Direct_Mem, "  %c%6zu bytes [%s:%d in %s()] (%s%zu) <- %p -> %p '%s'\n",
                           (bytes > desc->bytes) ? '>' : '<', bytes, file, line, func,
                           (bytes > desc->bytes) ? "+" : "", bytes - desc->bytes, mem, new_mem, what);

               if (desc->trace) {
                    direct_trace_free_buffer( desc->trace );
                    desc->trace = NULL;
               }

               if (!new_mem) {
                    D_WARN( "could not reallocate memory (%p: %zu->%zu)", mem, desc->bytes, bytes );

                    alloc_count--;


                    if (i < alloc_count)
                         direct_memmove( desc, desc + 1, (alloc_count - i) * sizeof(MemDesc) );
               }
               else
                    fill_mem_desc( desc, new_mem, bytes, func, file, line, direct_trace_copy_buffer(NULL) );

               pthread_mutex_unlock( &alloc_lock );

               return new_mem;
          }
     }

     pthread_mutex_unlock( &alloc_lock );

     D_ERROR( "Direct/Mem: Not reallocating unknown %p (%s) from [%s:%d in %s()] - corrupt/incomplete list?\n",
              mem, what, file, line, func );

     return direct_malloc( file, line, func, bytes );
}
