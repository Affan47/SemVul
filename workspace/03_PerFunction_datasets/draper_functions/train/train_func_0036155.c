xQueueGenericReceive( xQueueHandle pxQueue, void * const pvBuffer, portTickType xTicksToWait, portBASE_TYPE xJustPeeking )
{
signed portBASE_TYPE xEntryTimeSet = pdFALSE;
xTimeOutType xTimeOut;
signed char *pcOriginalReadPosition;

	configASSERT( pxQueue );
	configASSERT( !( ( pvBuffer == NULL ) && ( pxQueue->uxItemSize != ( unsigned portBASE_TYPE ) 0U ) ) );


	for( ;; )
	{
		taskENTER_CRITICAL();
		{


			if( pxQueue->uxMessagesWaiting > ( unsigned portBASE_TYPE ) 0 )
			{

				pcOriginalReadPosition = pxQueue->pcReadFrom;

				prvCopyDataFromQueue( pxQueue, pvBuffer );

				if( xJustPeeking == pdFALSE )
				{
					traceQUEUE_RECEIVE( pxQueue );


					--( pxQueue->uxMessagesWaiting );

					#if ( configUSE_MUTEXES == 1 )
					{
						if( pxQueue->uxQueueType == queueQUEUE_IS_MUTEX )
						{


							pxQueue->pxMutexHolder = xTaskGetCurrentTaskHandle();
						}
					}
					#endif

					if( listLIST_IS_EMPTY( &( pxQueue->xTasksWaitingToSend ) ) == pdFALSE )
					{
						if( xTaskRemoveFromEventList( &( pxQueue->xTasksWaitingToSend ) ) == pdTRUE )
						{
							portYIELD_WITHIN_API();
						}
					}
				}
				else
				{
					traceQUEUE_PEEK( pxQueue );


					pxQueue->pcReadFrom = pcOriginalReadPosition;


					if( listLIST_IS_EMPTY( &( pxQueue->xTasksWaitingToReceive ) ) == pdFALSE )
					{


						if( xTaskRemoveFromEventList( &( pxQueue->xTasksWaitingToReceive ) ) != pdFALSE )
						{

							portYIELD_WITHIN_API();
						}
					}
				}

				taskEXIT_CRITICAL();
				return pdPASS;
			}
			else
			{
				if( xTicksToWait == ( portTickType ) 0 )
				{


					taskEXIT_CRITICAL();
					traceQUEUE_RECEIVE_FAILED( pxQueue );
					return errQUEUE_EMPTY;
				}
				else if( xEntryTimeSet == pdFALSE )
				{


					vTaskSetTimeOutState( &xTimeOut );
					xEntryTimeSet = pdTRUE;
				}
			}
		}
		taskEXIT_CRITICAL();


		vTaskSuspendAll();
		prvLockQueue( pxQueue );


		if( xTaskCheckForTimeOut( &xTimeOut, &xTicksToWait ) == pdFALSE )
		{
			if( prvIsQueueEmpty( pxQueue ) != pdFALSE )
			{
				traceBLOCKING_ON_QUEUE_RECEIVE( pxQueue );

				#if ( configUSE_MUTEXES == 1 )
				{
					if( pxQueue->uxQueueType == queueQUEUE_IS_MUTEX )
					{
						portENTER_CRITICAL();
						{
							vTaskPriorityInherit( ( void * ) pxQueue->pxMutexHolder );
						}
						portEXIT_CRITICAL();
					}
				}
				#endif

				vTaskPlaceOnEventList( &( pxQueue->xTasksWaitingToReceive ), xTicksToWait );
				prvUnlockQueue( pxQueue );
				if( xTaskResumeAll() == pdFALSE )
				{
					portYIELD_WITHIN_API();
				}
			}
			else
			{

				prvUnlockQueue( pxQueue );
				( void ) xTaskResumeAll();
			}
		}
		else
		{
			prvUnlockQueue( pxQueue );
			( void ) xTaskResumeAll();
			traceQUEUE_RECEIVE_FAILED( pxQueue );
			return errQUEUE_EMPTY;
		}
	}
}
