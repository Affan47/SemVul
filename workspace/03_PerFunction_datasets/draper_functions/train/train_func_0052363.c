direct_cleanup_handler_remove( DirectCleanupHandler *handler )
{
     D_ASSERT( handler != NULL );

     D_MAGIC_ASSERT( handler, DirectCleanupHandler );

     D_DEBUG_AT( Direct_Main, "Removing cleanup handler %p with context %p...\n",
                 handler->func, handler->ctx );

     pthread_mutex_lock( &main_lock );
     direct_list_remove( &handlers, &handler->link );
     pthread_mutex_unlock( &main_lock );

     D_MAGIC_CLEAR( handler );

     D_FREE( handler );

     return DR_OK;
}
