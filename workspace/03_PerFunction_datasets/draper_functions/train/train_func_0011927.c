xQueueIsQueueFullFromISR( const xQueueHandle pxQueue )
{
signed portBASE_TYPE xReturn;

	configASSERT( pxQueue );
	xReturn = ( pxQueue->uxMessagesWaiting == pxQueue->uxLength );

	return xReturn;
}
