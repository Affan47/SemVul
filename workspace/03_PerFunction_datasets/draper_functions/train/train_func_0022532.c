fusion_shm_pool_detach( FusionSHM           *shm,
                        FusionSHMPoolShared *pool )
{
     D_MAGIC_ASSERT( pool, FusionSHMPoolShared );

     D_ASSERT( pool->index > 0 );

     pool->index--;

     return DR_OK;
}
