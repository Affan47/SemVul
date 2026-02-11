fusion_arena_enter (FusionWorld    *world,
                    const char     *name,
                    ArenaEnterFunc  initialize,
                    ArenaEnterFunc  join,
                    void           *ctx,
                    FusionArena   **ret_arena,
                    int            *ret_error)
{
     int error;

     D_ASSERT( name != NULL );
     D_ASSERT( initialize != NULL );
     D_ASSERT( join != NULL );
     D_ASSERT( ret_arena != NULL );


     error = initialize (NULL, ctx);


     if (ret_error)
          *ret_error = error;

     return DR_OK;
}
