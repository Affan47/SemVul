wm_get_window_property( CoreWindowStack  *stack,
                        void             *wm_data,
                        void             *stack_data,
                        CoreWindow       *window,
                        void             *window_data,
                        const char       *key,
                        void            **ret_value )
{
     D_ASSERT( stack != NULL );
     D_ASSERT( wm_data != NULL );
     D_ASSERT( stack_data != NULL );
     D_ASSERT( window != NULL );
     D_ASSERT( window_data != NULL );
     D_ASSERT( key != NULL );
     D_ASSERT( ret_value != NULL );

     *ret_value = fusion_object_get_property((FusionObject*)window,key);
     return DFB_OK;
}
