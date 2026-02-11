dfb_input_set_global( ReactionFunc func,
                      int          index )
{
     D_DEBUG_AT( Core_Input, "%s( %p, %d )\n", __FUNCTION__, func, index );

     D_ASSERT( func != NULL );
     D_ASSERT( index >= 0 );
     D_ASSERT( index < MAX_INPUT_GLOBALS );

     D_ASSUME( dfb_input_globals[index] == NULL );

     dfb_input_globals[index] = func;

     return DFB_OK;
}
