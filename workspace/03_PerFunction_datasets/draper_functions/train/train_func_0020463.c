vpsmemAllocateBuffer( CoreSurfacePool       *pool,
                      void                  *pool_data,
                      void                  *pool_local,
                      CoreSurfaceBuffer     *buffer,
                      CoreSurfaceAllocation *allocation,
                      void                  *alloc_data )
{
     DFBResult             ret;
     Chunk                *chunk;
     CoreSurface          *surface;
     VPSMemPoolData       *data  = pool_data;
     VPSMemPoolLocalData  *local = pool_local;
     VPSMemAllocationData *alloc = alloc_data;

     D_DEBUG_AT( VPSMem_Surfaces, "%s( %p )\n", __FUNCTION__, buffer );

     D_MAGIC_ASSERT( pool, CoreSurfacePool );
     D_MAGIC_ASSERT( data, VPSMemPoolData );
     D_MAGIC_ASSERT( local, VPSMemPoolLocalData );
     D_MAGIC_ASSERT( buffer, CoreSurfaceBuffer );

     surface = buffer->surface;
     D_MAGIC_ASSERT( surface, CoreSurface );

     ret = dfb_surfacemanager_allocate( local->core, data->manager, buffer, allocation, &chunk );
     if (ret)
          return ret;

     D_MAGIC_ASSERT( chunk, Chunk );

     alloc->offset = chunk->offset;
     alloc->pitch  = chunk->pitch;
     alloc->size   = surface->config.size.h * alloc->pitch;

     alloc->chunk  = chunk;

     D_DEBUG_AT( VPSMem_Surfaces, "  -> offset %d, pitch %d, size %d (%d)\n",
                 alloc->offset, alloc->pitch, alloc->size, chunk->length );

     D_ASSERT( chunk->length >= alloc->size );

     alloc->size = chunk->length;

     allocation->size   = alloc->size;
     allocation->offset = alloc->offset;

     D_MAGIC_SET( alloc, VPSMemAllocationData );

     return DFB_OK;
}
