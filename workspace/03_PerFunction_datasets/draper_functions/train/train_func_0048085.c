prvInitialiseTCBVariables( TCB_t * const pxTCB, const char * const pcName, UBaseType_t uxPriority, const MemoryRegion_t * const xRegions, const uint16_t usStackDepth )
{
UBaseType_t x;


	for( x = ( UBaseType_t ) 0; x < ( UBaseType_t ) configMAX_TASK_NAME_LEN; x++ )
	{
		pxTCB->pcTaskName[ x ] = pcName[ x ];


		if( pcName[ x ] == 0x00 )
		{
			break;
		}
		else
		{
			mtCOVERAGE_TEST_MARKER();
		}
	}


	pxTCB->pcTaskName[ configMAX_TASK_NAME_LEN - 1 ] = '\0';


	if( uxPriority >= ( UBaseType_t ) configMAX_PRIORITIES )
	{
		uxPriority = ( UBaseType_t ) configMAX_PRIORITIES - ( UBaseType_t ) 1U;
	}
	else
	{
		mtCOVERAGE_TEST_MARKER();
	}

	pxTCB->uxPriority = uxPriority;
	#if ( configUSE_MUTEXES == 1 )
	{
		pxTCB->uxBasePriority = uxPriority;
		pxTCB->uxMutexesHeld = 0;
	}
	#endif

	vListInitialiseItem( &( pxTCB->xGenericListItem ) );
	vListInitialiseItem( &( pxTCB->xEventListItem ) );


	listSET_LIST_ITEM_OWNER( &( pxTCB->xGenericListItem ), pxTCB );


	listSET_LIST_ITEM_VALUE( &( pxTCB->xEventListItem ), ( TickType_t ) configMAX_PRIORITIES - ( TickType_t ) uxPriority );
	listSET_LIST_ITEM_OWNER( &( pxTCB->xEventListItem ), pxTCB );

	#if ( portCRITICAL_NESTING_IN_TCB == 1 )
	{
		pxTCB->uxCriticalNesting = ( UBaseType_t ) 0U;
	}
	#endif

	#if ( configUSE_APPLICATION_TASK_TAG == 1 )
	{
		pxTCB->pxTaskTag = NULL;
	}
	#endif

	#if ( configGENERATE_RUN_TIME_STATS == 1 )
	{
		pxTCB->ulRunTimeCounter = 0UL;
	}
	#endif

	#if ( portUSING_MPU_WRAPPERS == 1 )
	{
		vPortStoreTaskMPUSettings( &( pxTCB->xMPUSettings ), xRegions, pxTCB->pxStack, usStackDepth );
	}
	#else
	{
		( void ) xRegions;
		( void ) usStackDepth;
	}
	#endif

	#if( configNUM_THREAD_LOCAL_STORAGE_POINTERS != 0 )
	{
		for( x = 0; x < ( UBaseType_t ) configNUM_THREAD_LOCAL_STORAGE_POINTERS; x++ )
		{
			pxTCB->pvThreadLocalStoragePointers[ x ] = NULL;
		}
	}
	#endif

	#if ( configUSE_TASK_NOTIFICATIONS == 1 )
	{
		pxTCB->ulNotifiedValue = 0;
		pxTCB->eNotifyState = eNotWaitingNotification;
	}
	#endif

	#if ( configUSE_NEWLIB_REENTRANT == 1 )
	{

		_REENT_INIT_PTR( ( &( pxTCB->xNewLib_reent ) ) );
	}
	#endif
}
