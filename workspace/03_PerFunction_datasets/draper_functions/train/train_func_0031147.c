vTaskIncrementTick( void )
{
tskTCB * pxTCB;


	traceTASK_INCREMENT_TICK( xTickCount );
	if( uxSchedulerSuspended == ( unsigned portBASE_TYPE ) pdFALSE )
	{
		++xTickCount;
		if( xTickCount == ( portTickType ) 0U )
		{
			xList *pxTemp;


			configASSERT( ( listLIST_IS_EMPTY( pxDelayedTaskList ) ) );

			pxTemp = pxDelayedTaskList;
			pxDelayedTaskList = pxOverflowDelayedTaskList;
			pxOverflowDelayedTaskList = pxTemp;
			xNumOfOverflows++;

			if( listLIST_IS_EMPTY( pxDelayedTaskList ) != pdFALSE )
			{


				xNextTaskUnblockTime = portMAX_DELAY;
			}
			else
			{


				pxTCB = ( tskTCB * ) listGET_OWNER_OF_HEAD_ENTRY( pxDelayedTaskList );
				xNextTaskUnblockTime = listGET_LIST_ITEM_VALUE( &( pxTCB->xGenericListItem ) );
			}
		}


		prvCheckDelayedTasks();
	}
	else
	{
		++uxMissedTicks;


		#if ( configUSE_TICK_HOOK == 1 )
		{
			vApplicationTickHook();
		}
		#endif
	}

	#if ( configUSE_TICK_HOOK == 1 )
	{


		if( uxMissedTicks == ( unsigned portBASE_TYPE ) 0U )
		{
			vApplicationTickHook();
		}
	}
	#endif
}
