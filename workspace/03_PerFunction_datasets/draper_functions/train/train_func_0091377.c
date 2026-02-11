allocate_mem_desc( void )
{
     int cap = alloc_capacity;

     if (!cap)
          cap = 64;
     else if (cap == alloc_count)
          cap <<= 1;

     if (cap != alloc_capacity) {
          void *new_list = malloc( sizeof(MemDesc) * cap );

          if (!new_list) {
               D_WARN( "could not allocate more descriptors (%d->%d)", alloc_capacity, cap );
               return NULL;
          }

          direct_memcpy( new_list, alloc_list, sizeof(MemDesc) * alloc_count );

          free( alloc_list );

          alloc_capacity = cap;
          alloc_list     = new_list;
     }

     return &alloc_list[alloc_count++];
}
