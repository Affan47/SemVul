remove_all_filters( UniqueWindow *window )
{
     DirectLink    *n;
     KeyFilter     *key;
     UniqueContext *context;

     D_MAGIC_ASSERT( window, UniqueWindow );

     context = window->context;

     D_MAGIC_ASSERT( context, UniqueContext );

     direct_list_foreach_safe (key, n, window->filters) {
          D_MAGIC_ASSERT( key, KeyFilter );

          unique_input_switch_unset_filter( context->input_switch, key->filter );

          D_MAGIC_CLEAR( key );

          SHFREE( context->shmpool, key );
     }

     window->filters = NULL;
}
