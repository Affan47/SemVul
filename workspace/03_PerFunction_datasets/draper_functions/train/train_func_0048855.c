fusion_shmalloc (FusionSHMPoolShared *pool,
                 size_t __size)
{
     D_MAGIC_ASSERT( pool, FusionSHMPoolShared );
     D_ASSERT( __size > 0 );

     if (pool->debug)
          D_WARN( "Fusion/SHMMalloc: Pool runs in debug mode, but access from pure-release is attempted!\n" );

     return malloc( __size );
}
