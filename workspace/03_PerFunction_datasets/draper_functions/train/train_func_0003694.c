xQueueIsQueueEmptyFromISR( const xQueueHandle pxQueue )
{
signed portBASE_TYPE xReturn;

	configASSERT( pxQueue );
	xReturn = ( pxQueue->uxMessagesWaiting == ( unsigned portBASE_TYPE ) 0 );

	return xReturn;
}
