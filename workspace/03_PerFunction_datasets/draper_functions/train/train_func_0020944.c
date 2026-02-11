xTimerCreateTimerTask( void )
{
portBASE_TYPE xReturn = pdFAIL;


	prvCheckForValidListAndQueue();

	if( xTimerQueue != NULL )
	{
		#if ( INCLUDE_xTimerGetTimerDaemonTaskHandle == 1 )
		{


			xReturn = xTaskCreate( prvTimerTask, ( const signed char * ) "Tmr Svc", ( unsigned short ) configTIMER_TASK_STACK_DEPTH, NULL, ( ( unsigned portBASE_TYPE ) configTIMER_TASK_PRIORITY ) | portPRIVILEGE_BIT, &xTimerTaskHandle );
		}
		#else
		{

			xReturn = xTaskCreate( prvTimerTask, ( const signed char * ) "Tmr Svc", ( unsigned short ) configTIMER_TASK_STACK_DEPTH, NULL, ( ( unsigned portBASE_TYPE ) configTIMER_TASK_PRIORITY ) | portPRIVILEGE_BIT, NULL);
		}
		#endif
	}

	configASSERT( xReturn );
	return xReturn;
}
