dfb_colorhash_attach( DFBColorHashCore *core,
                      CorePalette      *palette )
{
     DFBColorHashCoreShared *shared;

     D_ASSUME( core != NULL );

     if (core) {
          D_MAGIC_ASSERT( core, DFBColorHashCore );
          D_MAGIC_ASSERT( core->shared, DFBColorHashCoreShared );
     }
     else
          core = core_colorhash;

     shared = core->shared;

     fusion_skirmish_prevail( &shared->hash_lock );

     if (!shared->hash) {
          D_ASSERT( shared->hash_users == 0 );

          shared->hash = SHCALLOC( shared->shmpool, HASH_SIZE, sizeof (Colorhash) );
     }

     shared->hash_users++;

     fusion_skirmish_dismiss( &shared->hash_lock );
}
