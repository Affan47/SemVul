xQueueReceiveFromISR( xQueueHandle pxQueue, void * const pvBuffer, signed portBASE_TYPE *pxHigherPriorityTaskWoken )
{
signed portBASE_TYPE xReturn;
unsigned portBASE_TYPE uxSavedInterruptStatus;

	configASSERT( pxQueue );
	configASSERT( !( ( pvBuffer == NULL ) && ( pxQueue->uxItemSize != ( unsigned portBASE_TYPE ) 0U ) ) );

	uxSavedInterruptStatus = portSET_INTERRUPT_MASK_FROM_ISR();
	{

		if( pxQueue->uxMessagesWaiting > ( unsigned portBASE_TYPE ) 0 )
		{
			traceQUEUE_RECEIVE_FROM_ISR( pxQueue );

			prvCopyDataFromQueue( pxQueue, pvBuffer );
			--( pxQueue->uxMessagesWaiting );


			if( pxQueue->xRxLock == queueUNLOCKED )
			{
				if( listLIST_IS_EMPTY( &( pxQueue->xTasksWaitingToSend ) ) == pdFALSE )
				{
					if( xTaskRemoveFromEventList( &( pxQueue->xTasksWaitingToSend ) ) != pdFALSE )
					{


						if( pxHigherPriorityTaskWoken != NULL )
						{
							*pxHigherPriorityTaskWoken = pdTRUE;
						}
					}
				}
			}
			else
			{


				++( pxQueue->xRxLock );
			}

			xReturn = pdPASS;
		}
		else
		{
			xReturn = pdFAIL;
			traceQUEUE_RECEIVE_FROM_ISR_FAILED( pxQueue );
		}
	}
	portCLEAR_INTERRUPT_MASK_FROM_ISR( uxSavedInterruptStatus );

	return xReturn;
}
