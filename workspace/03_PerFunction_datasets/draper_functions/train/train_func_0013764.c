fusion_reactor_attach (FusionReactor *reactor,
                       ReactionFunc   func,
                       void          *ctx,
                       Reaction      *reaction)
{
     D_ASSERT( reactor != NULL );
     D_ASSERT( func != NULL );
     D_ASSERT( reaction != NULL );

     reaction->func = func;
     reaction->ctx  = ctx;

     pthread_mutex_lock( &reactor->reactions_lock );

     direct_list_prepend( &reactor->reactions, &reaction->link );

     pthread_mutex_unlock( &reactor->reactions_lock );

     return DR_OK;
}
