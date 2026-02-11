dfb_windowstack_lock( CoreWindowStack *stack )
{
     D_MAGIC_ASSERT( stack, CoreWindowStack );
     D_ASSERT( stack->context != NULL );

     return dfb_layer_context_lock( stack->context );
}
