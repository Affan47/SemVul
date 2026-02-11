wm_update_stack( CoreWindowStack     *stack,
                 void                *wm_data,
                 void                *stack_data,
                 const DFBRegion     *region,
                 DFBSurfaceFlipFlags  flags )
{
     StackData *data = stack_data;

     D_ASSERT( stack != NULL );
     D_ASSERT( wm_data != NULL );
     D_ASSERT( stack_data != NULL );
     D_ASSERT( region != NULL );

     D_MAGIC_ASSERT( data, StackData );

     dfb_updates_add( &data->updates, region );

     process_updates( data, wm_data, stack, NULL, flags );

     return DFB_OK;
}
