dfb_gfxcard_invalidate_state( void )
{
     D_ASSERT( card != NULL );
     D_ASSERT( card->shared != NULL );

     card->shared->state = NULL;
}
