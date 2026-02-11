wm_close_stack( CoreWindowStack *stack,
                void            *wm_data,
                void            *stack_data )
{
     StackData *data = stack_data;

     D_ASSERT( stack != NULL );
     D_ASSERT( wm_data != NULL );
     D_ASSERT( stack_data != NULL );

     D_MAGIC_ASSERT( data, StackData );

     D_ASSUME( data->context == NULL );

     if (data->context)
          unique_context_detach_global( data->context, &data->context_reaction );

     D_MAGIC_CLEAR( data );

     return DFB_OK;
}
